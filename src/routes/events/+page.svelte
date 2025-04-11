<script lang="ts">
  import EventCard from '../../lib/EventCard.svelte';

  export let data;
  let { supabase, session } = data;

  type Event = {
    id: number;
    title: string;
    description: string;
    start_date: string;
    end_date: string;
    location: string;
    venue: string;
    isFavorite: boolean;
    video_link?: string;
  };

  let events: Event[] = [];
  let userRole: number | null = null;

  async function fetchUserRole() {
    if (!session?.user?.id || !supabase) return;

    const { data, error } = await supabase
      .from('profiles')
      .select('role')
      .eq('id', session.user.id)
      .single();

    if (error) {
      console.error("Error fetching user role:", error.message);
      return;
    }

    userRole = data?.role ?? null;
  }

  async function fetchEvents() {
    if (!supabase) return;

    const { data, error } = await supabase.from('conferences').select('*');
    if (error) {
      console.error("Error fetching events:", error.message);
      return;
    }

    events = data.map(e => ({
      id: e.id,
      title: e.title,
      description: e.description,
      start_date: e.start_date,
      end_date: e.end_date,
      location: e.location,
      venue: e.venue,
      isFavorite: false,
    }));
  }

  function convertToEmbedUrl(url: string): string {
    const regex = /(?:https?:\/\/)?(?:www\.)?youtube\.com\/watch\?v=([^&]+)/;
    const shortRegex = /(?:https?:\/\/)?youtu\.be\/([^?]+)/;

    let match = url.match(regex) || url.match(shortRegex);
    return match ? `https://www.youtube.com/embed/${match[1]}` : url;
  }

  async function toggleFavorite(eventId: number): Promise<void> {
    const event = events.find(e => e.id === eventId);
    if (!event || !session?.user?.id) return;

    const originalFavoriteState = event.isFavorite;
    event.isFavorite = !event.isFavorite;
    events = [...events];

    const userId = session.user.id;

    if (event.isFavorite) {
      const { error } = await supabase.from('conference_participants').insert([
        { conference_id: event.id, user_id: userId, is_favourited: true }
      ]);

      if (error) {
        console.error("Error adding participant:", error.message);
        event.isFavorite = originalFavoriteState;
      }
    } else {
      const { error } = await supabase
        .from('conference_participants')
        .delete()
        .match({ conference_id: event.id, user_id: userId });

      if (error) {
        console.error("Error removing participant:", error.message);
        event.isFavorite = originalFavoriteState;
      }
    }

    events = [...events];
  }

  let newEvent: Event = {
    id: 0,
    title: "",
    description: "",
    start_date: "",
    end_date: "",
    location: "",
    venue: "",
    isFavorite: false,
    video_link: ""
  };

  async function addEvent() {
    if (!newEvent.title) {
      console.log("Missing title");
    }
    if (!newEvent.start_date) {
      console.log("Missing start_date");
    }
    if (!newEvent.end_date) {
      console.log("Missing end_date");
    }
    if (!newEvent.location) {
      console.log("Missing location");
    }
    if (!newEvent.venue) {
      console.log("Missing venue");
    }

    //if (!newEvent.title || !newEvent.start_date || !newEvent.end_date || !newEvent.location || !newEvent.venue) {
    //  return;
    //}
    
    const embedUrl = newEvent.video_link ? convertToEmbedUrl(newEvent.video_link) : null;

    const { error } = await supabase.from('conferences').insert([
      {
        title: newEvent.title,
        description: newEvent.description,
        start_date: newEvent.start_date,
        end_date: newEvent.end_date,
        location: newEvent.location,
        venue: newEvent.venue,
        video_link: embedUrl
      }
    ]);

    if (error) {
      console.error("Error adding event:", error.message);
      return;
    }

    await fetchEvents();

    newEvent = {
      id: 0,
      title: "",
      description: "",
      start_date: "",
      end_date: "",
      location: "",
      venue: "",
      isFavorite: false,
      video_link: ""
    };
  }

  fetchEvents();
  fetchUserRole();
</script>

<div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden flex flex-col items-center">
  <h2 class="text-3xl font-bold text-pink-400 text-center">Wydarzenia</h2>

  {#if userRole !== 0}
    <div class="bg-gray-900 p-6 rounded-lg shadow-lg w-96 text-white">
      <h3 class="text-xl font-bold mb-4 text-center">Dodaj nowe wydarzenie</h3>
      <div class="flex flex-col gap-3">
        <input bind:value={newEvent.title} placeholder="Tytuł wydarzenia" class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.description} placeholder="Opis" class="p-2 rounded bg-gray-800 text-white" />
        <input type="date" bind:value={newEvent.start_date} class="p-2 rounded bg-gray-800 text-white" />
        <input type="date" bind:value={newEvent.end_date} class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.location} placeholder="Lokalizacja" class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.video_link} placeholder="Opcjonalny link YouTube" class="p-2 rounded bg-gray-800 text-white" />
        <button on:click={addEvent} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">Dodaj wydarzenie</button>
      </div>
    </div>
  {/if}

  <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8 px-6 mt-8">
    {#each events as event} <EventCard {event} {toggleFavorite} /> {/each}
  </div>
</div>
