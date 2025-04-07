<script lang="ts">
  import EventCard from '../../lib/EventCard.svelte';

  export let data;
  let { supabase, session } = data;

  type event = {
    id: number;
    name: string;
    description: string;
    date: string;
    time: string;
    location: string;
    isFavorite: boolean;
  };

  let events: event[] = [];

  function formatTableName(email: string): string {
    return email.replace(/@/g, '_at_').replace(/\./g, '_dot_');
  }

  async function fetchEvents() {
    const { data, error } = await supabase.from('global_events').select('*');
    if (error) {
      console.error("Error fetching events:", error.message);
      return;
    }

    // Map fetched data to our event structure
    events = data.map(e => ({
      id: e.id,
      name: e.event_name,
      description: e.event_desc,
      date: e.event_date,
      time: e.event_time,
      location: e.event_loc,
      isFavorite: false
    }));
  }

  async function toggleFavorite(eventId: number): Promise<void> {
    const event = events.find(e => e.id === eventId);
    if (!event || !session?.user?.email) return;

    event.isFavorite = !event.isFavorite;
    events = [...events];

    const tableName = formatTableName(session.user.email);

    if (event.isFavorite) {
      // Add to favorites in Supabase
      const { error } = await supabase.from(tableName).insert([
        {
          event_name: event.name,
          event_desc: event.description,
          event_date: event.date,
          event_time: event.time,
          event_loc: event.location,
        }
      ]);

      if (error) {
        console.error("Error adding to favorites:", error.message);
        event.isFavorite = false; // Revert if there's an error
      }
    } else {
      // Remove from favorites in Supabase
      const { error } = await supabase.from(tableName).delete().match({ event_ID: event.id });

      if (error) {
        console.error("Error removing from favorites:", error.message);
        event.isFavorite = true; // Revert if there's an error
      }
    }

    events = [...events];
  }

  let newEvent: event = {
    name: "",
    description: "",
    date: "",
    time: "",
    location: "",
    isFavorite: false
  };

  async function addEvent() {
    if (!newEvent.name || !newEvent.date || !newEvent.time || !newEvent.location) return;

    // Push to global_events table in Supabase
    const { error } = await supabase.from('global_events').insert([
      {
        event_name: newEvent.name,
        event_desc: newEvent.description,
        event_date: newEvent.date,
        event_time: newEvent.time,
        event_loc: newEvent.location,
      }
    ]);

    if (error) {
      console.error("Error adding event to global_events:", error.message);
      return;
    }

    // Re-fetch events to update UI
    await fetchEvents();

    // Reset form fields
    newEvent = { name: "", description: "", date: "", time: "", location: "", isFavorite: false };
  }

  // Fetch events when component loads
  fetchEvents();
</script>

<div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden flex flex-col items-center">
  <h2 class="text-3xl font-bold text-pink-400 text-center">Wydarzenia</h2>

  <div class="bg-gray-900 p-6 rounded-lg shadow-lg w-96 text-white">
    <h3 class="text-xl font-bold mb-4 text-center">Dodaj nowe wydarzenie</h3>
    <div class="flex flex-col gap-3">
      <input type="text" bind:value={newEvent.name} placeholder="Nazwa wydarzenia" class="p-2 rounded bg-gray-800 text-white" />
      <input type="text" bind:value={newEvent.description} placeholder="Opis" class="p-2 rounded bg-gray-800 text-white" />
      <input type="date" bind:value={newEvent.date} class="p-2 rounded bg-gray-800 text-white" />
      <input type="time" bind:value={newEvent.time} class="p-2 rounded bg-gray-800 text-white" />
      <input type="text" bind:value={newEvent.location} placeholder="Lokalizacja" class="p-2 rounded bg-gray-800 text-white" />
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
