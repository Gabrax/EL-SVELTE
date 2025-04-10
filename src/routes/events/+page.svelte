<script lang="ts">
  import EventCard from '../../lib/EventCard.svelte';

  export let data;
  let { supabase, session } = data;

  type event = {
    id: number;
    title: string;
    description: string;
    start_date: string;
    end_date: string;
    location: string;
    venue: string;
    isFavorite: boolean;
  };

  let events: event[] = [];

  async function fetchEvents() {
    const { data, error } = await supabase.from('conferences').select('*');
    if (error) {
      console.error("Error fetching events:", error.message);
      return;
    }

    // Map fetched data to our event structure
    events = data.map(e => ({
      id: e.id,
      title: e.title,
      description: e.description,
      start_date: e.start_date,
      end_date: e.end_date,
      location: e.location,
      venue: e.venue,
      isFavorite: false
    }));
  }

  async function toggleFavorite(eventId: number): Promise<void> {
      const event = events.find(e => e.id === eventId);
      if (!event || !session?.user?.id) return;

      event.isFavorite = !event.isFavorite;
      events = [...events];

      const userId = session.user.id;

      if (event.isFavorite) {

          const { error: participantError } = await supabase.from('conference_participants').insert([
              {
                  conference_id: event.id,
                  user_id: userId,
                  is_favourited: true
              }
          ]);

          if (participantError) {
              console.error("Error adding participant record:", participantError.message);
              event.isFavorite = false; // Revert if there's an error
          }
      } else {
          const { error: participantRemoveError } = await supabase
              .from('conference_participants')
              .delete()
              .match({ conference_id: event.id, user_id: userId });

          if (participantRemoveError) {
              console.error("Error removing participant record:", participantRemoveError.message);
              event.isFavorite = true; // Revert if there's an error
          }
      }

      events = [...events];
  }


  let newEvent: event = {
    id: 0,
    title: "",
    description: "",
    start_date: "",
    end_date: "",
    location: "",
    venue: "",
    isFavorite: false
  };

  async function addEvent() {
    if (!newEvent.title || !newEvent.start_date || !newEvent.end_date || !newEvent.location || !newEvent.venue) return;

    // Push to conferences table in Supabase
    const { error } = await supabase.from('conferences').insert([
      {
        title: newEvent.title,
        description: newEvent.description,
        start_date: newEvent.start_date,
        end_date: newEvent.end_date,
        location: newEvent.location,
        venue: newEvent.venue,
      }
    ]);

    if (error) {
      console.error("Error adding event to conferences:", error.message);
      return;
    }

    // Re-fetch events to update UI
    await fetchEvents();

    // Reset form fields
    newEvent = {
      id: 0,
      title: "",
      description: "",
      start_date: "",
      end_date: "",
      location: "",
      venue: "",
      isFavorite: false
    };
  }

  // Fetch events when component loads
  fetchEvents();
</script>

<div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden flex flex-col items-center">
  <h2 class="text-3xl font-bold text-pink-400 text-center">Wydarzenia</h2>

  <div class="bg-gray-900 p-6 rounded-lg shadow-lg w-96 text-white">
    <h3 class="text-xl font-bold mb-4 text-center">Dodaj nowe wydarzenie</h3>
    <div class="flex flex-col gap-3">
      <input type="text" bind:value={newEvent.title} placeholder="Tytuł wydarzenia" class="p-2 rounded bg-gray-800 text-white" />
      <input type="text" bind:value={newEvent.description} placeholder="Opis" class="p-2 rounded bg-gray-800 text-white" />
      <input type="date" bind:value={newEvent.start_date} class="p-2 rounded bg-gray-800 text-white" />
      <input type="date" bind:value={newEvent.end_date} class="p-2 rounded bg-gray-800 text-white" />
      <input type="text" bind:value={newEvent.location} placeholder="Lokalizacja" class="p-2 rounded bg-gray-800 text-white" />
      <input type="text" bind:value={newEvent.venue} placeholder="Miejsce wydarzenia" class="p-2 rounded bg-gray-800 text-white" />
      <button on:click={addEvent} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">
        Dodaj wydarzenie
      </button>
    </div>
  </div>

  <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8 px-6 mt-8">
    {#each events as event}
      <div class="hover:shadow-lg transition">
        <EventCard {event} {toggleFavorite} />
      </div>
    {/each}
  </div>
</div>
