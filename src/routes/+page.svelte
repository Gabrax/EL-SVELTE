<script lang="ts">
  import { goto } from '$app/navigation';
  import EventCard from '../lib/EventCard.svelte';

  export let data;
  let { supabase, session } = data;
  $: ({ supabase, session } = data);

  type Event = {
    id: number;
    user_id: number;
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
  let showModal = false;


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

    let favoriteIds: number[] = [];

    if (session?.user?.id) {
      const { data: favs, error: favsError } = await supabase
        .from('conference_participants')
        .select('conference_id')
        .eq('user_id', session.user.id)
        .eq('is_favourited', true);

      if (favsError) {
        console.error("Error fetching favorites:", favsError.message);
      } else {
        favoriteIds = favs.map(f => f.conference_id);
      }
    }

    events = data.map(e => ({
      id: e.id,
      user_id: e.user_id,
      title: e.title,
      description: e.description,
      start_date: e.start_date,
      end_date: e.end_date,
      location: e.location,
      venue: e.venue,
      isFavorite: favoriteIds.includes(e.id),
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
    user_id: 0,
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

 //if (!newEvent.title && !newEvent.start_date || !newEvent.end_date || !newEvent.location || !newEvent.venue) {
    //  return;
    //}

    const userId = session.user.id;
    
    const embedUrl = newEvent.video_link ? convertToEmbedUrl(newEvent.video_link) : null;

    const { error } = await supabase.from('conferences').insert([
      {
        user_id: userId, 
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
      user_id: 0,
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

  async function onEdit(updatedEvent: { id: number; title: string; description: string; start_date: string; end_date: string; location: string; venue: string; video_link: string | null }) {
    const { error } = await supabase
      .from('conferences')
      .update({
        title: updatedEvent.title,
        description: updatedEvent.description,
        start_date: updatedEvent.start_date,
        end_date: updatedEvent.end_date,
        location: updatedEvent.location,
        venue: updatedEvent.venue,
        video_link: updatedEvent.video_link ? convertToEmbedUrl(updatedEvent.video_link) : null
      })
      .eq('id', updatedEvent.id);

    if (error) {
      console.error("Error updating event:", error.message);
      return;
    }

        // Update the local events array to reflect the changes
    events = events.map(e => e.id === updatedEvent.id ? updatedEvent : e);
  }

  async function deleteEvent(eventId: number) {
      const { error } = await supabase
        .from('conferences')
        .delete()
        .match({ id: eventId });

      if (error) {
        console.error("Error deleting event:", error.message);
        return;
      }

      // Remove the event from the local events array
      events = events.filter(e => e.id !== eventId);
    }

  function convertToCSV(events: Event[]): string {
    const header = ["id", "title", "description", "start_date", "end_date", "location", "venue", "video_link", "user_id"];
    
    const rows = events.map(event => [
      event.id,
      event.title,
      event.description,
      event.start_date,
      event.end_date,
      event.location,
      event.venue,
      event.video_link || '',
      event.user_id
    ].map(val => String(val).replace(/[\n\r,]/g, ' '))); 

    const csvContent = [
      header.join(","),           
      ...rows.map(row => row.join(","))  
    ].join("\n");

    return csvContent;
  }

  function exportToCSV() {
    const csvContent = convertToCSV(events);
    const blob = new Blob([csvContent], { type: "text/csv;charset=utf-8;" });
    const link = document.createElement("a");

    if (link.download !== undefined) {
      const url = URL.createObjectURL(blob);
      link.setAttribute("href", url);
      link.setAttribute("download", "wydarzenia.csv");
      link.style.visibility = "hidden";
      document.body.appendChild(link);
      link.click();
      document.body.removeChild(link);
    }
  }

  async function importCSV(event: Event) {
    const file = (event.target as HTMLInputElement).files?.[0];
    if (!file) return;

    const text = await file.text(); 
    const rows = parseCSV(text);  

    // Wstaw dane do bazy
    for (const row of rows) {
      const { title, description, start_date, end_date, location, venue, video_link, user_id } = row;

      const embedUrl = video_link ? convertToEmbedUrl(video_link) : null;

      const { error } = await supabase.from('conferences').insert([
        {
          title,
          description,
          start_date,
          end_date,
          location,
          venue,
          video_link: embedUrl,
          user_id,
        },
      ]);

      if (error) {
        console.error("Błąd podczas importu wydarzenia:", error.message);
        continue;  
      }
    }

    await fetchEvents(); 
  }

  function parseCSV(csvText: string): { title: string; description: string; start_date: string; end_date: string; location: string; venue: string; video_link: string | null; user_id: number }[] {
    const rows = csvText.split("\n").map(row => row.trim()).filter(row => row.length > 0);
    const header = rows[0].split(",");  
    const data = rows.slice(1);  

    return data.map(row => {
      const columns = row.split(",").map(col => col.trim());
      const event: { [key: string]: string } = {};

      header.forEach((col, idx) => {
        event[col] = columns[idx] || '';  
      });

      return {
        title: event['title'],
        description: event['description'],
        start_date: event['start_date'],
        end_date: event['end_date'],
        location: event['location'],
        venue: event['venue'],
        video_link: event['video_link'] || null,
        user_id: event['user_id'], 
      };
    });
  }

  

  fetchEvents();
  fetchUserRole();
</script>

<div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden flex flex-col items-center">
  <h2 class="text-3xl font-bold text-pink-400 text-center">Wydarzenia</h2>
  {#if session && userRole !== 0}
  <div class="flex space-x-4 mt-4">
    <button on:click={exportToCSV} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">
      Eksportuj do CSV
    </button>

    <label class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded cursor-pointer">
      Importuj z CSV
      <input type="file" accept=".csv" on:change={importCSV} class="hidden" />
    </label>

    <button on:click={() => showModal = true} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">
      Dodaj wydarzenie
    </button>
  </div>
  {/if}
  {#if !session}
    <p class="text-pink-300 text-sm mt-4">Zarejestruj się, aby uczestniczyć</p>
  {/if}
  <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8 px-6 mt-8">
    {#each events as event} <EventCard {event} onEdit={onEdit} deleteEvent={deleteEvent} {toggleFavorite} currentUserId={session?.user?.id ?? null} /> {/each}
  </div>

  {#if showModal}
  <div class="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50">
    <div class="bg-gray-900 p-6 rounded-lg shadow-lg w-[90%] max-w-md text-white relative">
      <button on:click={() => showModal = false} class="absolute top-2 right-2 text-white text-xl">✖</button>
      <h3 class="text-xl font-bold mb-4 text-center">Dodaj nowe wydarzenie</h3>
      <div class="flex flex-col gap-3">
        <input bind:value={newEvent.title} placeholder="Tytuł wydarzenia" class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.description} placeholder="Opis" class="p-2 rounded bg-gray-800 text-white" />
        <input type="date" bind:value={newEvent.start_date} class="p-2 rounded bg-gray-800 text-white" />
        <input type="date" bind:value={newEvent.end_date} class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.location} placeholder="Miasto" class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.venue} placeholder="Venue" class="p-2 rounded bg-gray-800 text-white" />
        <input bind:value={newEvent.video_link} placeholder="Opcjonalny link YouTube" class="p-2 rounded bg-gray-800 text-white" />
        <button on:click={() => { addEvent(); showModal = false; }} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">
          Dodaj wydarzenie
        </button>
      </div>
    </div>
  </div>
  {/if}
</div>

