<script lang="ts">
  import { onMount } from "svelte";
  import { createClient } from "@supabase/supabase-js";

  export let data;
  let { supabase, session } = data;

  type Event = {
    id: number;
    name: string;
    description: string;
    date: string;
    time?: string;
    location: string;
    isFavorite: boolean;
  };

  let events: Event[] = [];
  let today = new Date();
  let currentMonth = today.getMonth();
  let currentYear = today.getFullYear();
  let dates: (number | null)[] = [];
  let months = Array.from({ length: 12 }, (_, i) =>
    new Date(currentYear, i).toLocaleString("default", { month: "long" })
  );
  let hoveredEvents: Event[] = [];

  function formatTableName(email: string): string {
    return email.replace(/@/g, "_at_").replace(/\./g, "_dot_");
  }

  async function fetchEvents() {
    if (!session?.user?.email) return;

    const tableName = formatTableName(session.user.email);
    const { data, error } = await supabase.from(tableName).select("*");

    if (error) {
      console.error("Error fetching events:", error.message);
      return;
    }

    // Map the fetched data to the expected event structure
    events = data.map((event) => ({
      id: event.id,
      name: event.event_name,
      description: event.event_desc,
      date: event.event_date,
      time: event.event_time,
      location: event.event_loc,
      isFavorite: true,
    }));
  }

  function generateDates(year: number, month: number): (number | null)[] {
    const daysInMonth = new Date(year, month + 1, 0).getDate();
    const firstDay = new Date(year, month, 1).getDay();
    return Array(firstDay)
      .fill(null)
      .concat([...Array(daysInMonth).keys()].map((i) => i + 1));
  }

  $: dates = generateDates(currentYear, currentMonth);

  function changeMonth(direction: number): void {
    currentMonth += direction;
    if (currentMonth < 0) {
      currentMonth = 11;
      currentYear--;
    } else if (currentMonth > 11) {
      currentMonth = 0;
      currentYear++;
    }
    dates = generateDates(currentYear, currentMonth);
  }

  function getEventsForDay(day: number): Event[] {
    return events.filter((event) => {
      const eventDate = new Date(event.date);
      return (
        eventDate.getDate() === day &&
        eventDate.getMonth() === currentMonth &&
        eventDate.getFullYear() === currentYear
      );
    });
  }

  onMount(() => {
    fetchEvents();
  });
</script>

<div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden">
  <div class="text-center text-pink-400 my-5">
    <h2 class="text-3xl font-extrabold bg-gradient-to-r from-purple-400 to-blue-400 text-transparent bg-clip-text">
      {months[currentMonth]} {currentYear}
    </h2>
  </div>

  <div class="flex justify-between max-w-lg mx-auto mb-4">
    <button
      class="px-4 py-2 bg-gray-700 text-white rounded-md hover:bg-gray-600 transition"
      on:click={() => changeMonth(-1)}
    >
      Poprzedni
    </button>
    <button
      class="px-4 py-2 bg-gray-700 text-white rounded-md hover:bg-gray-600 transition"
      on:click={() => changeMonth(1)}
    >
      Następny
    </button>
  </div>

  <div class="grid grid-cols-7 gap-2 max-w-lg mx-auto text-center bg-[#1e293b] border border-pink-500 rounded-lg p-4 shadow-md">
    {#each ["Nd", "Pn", "Wt", "Śr", "Cz", "Pt", "Sb"] as day}
      <div class="py-2 font-bold text-lg text-gray-300">{day}</div>
    {/each}

    {#each dates as day}
      <div
        class="relative w-12 h-12 flex items-center justify-center text-lg font-semibold rounded-md transition-all
          {day === today.getDate() && currentMonth === today.getMonth() && currentYear === today.getFullYear() 
            ? 'bg-blue-600 text-white hover:scale-105' 
            : day && getEventsForDay(day).length > 0
                ? 'bg-pink-900/40 text-pink-200 hover:bg-pink-800/60 hover:scale-105'
                : 'bg-gray-700 text-gray-200 hover:bg-gray-600'}"
        on:mouseenter={() => hoveredEvents = getEventsForDay(day || 0)}
        on:mouseleave={() => hoveredEvents = []}
      >
        {day ? day : ""}
        {#if day && getEventsForDay(day).length > 0}
          <div class="absolute -top-1 -right-1 w-3 h-3 rounded-full bg-pink-500"></div>
        {/if}
      </div>
    {/each}
  </div>

  {#if hoveredEvents.length > 0}
    <div class="max-w-lg mx-auto mt-4 p-4 bg-[#1e293b] border border-pink-500 rounded-lg shadow-md">
      <h3 class="text-xl font-bold text-pink-400 mb-2">Szczegóły wydarzeń:</h3>
      <ul>
        {#each hoveredEvents as event}
          <li class="text-gray-300 mb-2">
            <strong>{event.name}</strong> - {event.description} ({event.location} {event.time})
          </li>
        {/each}
      </ul>
    </div>
  {/if}
</div>
