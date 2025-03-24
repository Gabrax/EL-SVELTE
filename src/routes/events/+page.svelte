
<script lang="ts">
    import { onMount } from "svelte";
    export let data;

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let events = []; // Stores events from the database
    let selectedEvent = null; // Stores the selected event for modal
    let isModalOpen = false;

    onMount(async () => {
        // Fetch events from Supabase
        const { data: eventsData, error } = await supabase
            .from("events")
            .select("*")
            .order("event_date", { ascending: true });

        if (eventsData) {
            events = eventsData;
        }
    });

    function openEvent(event) {
        selectedEvent = event;
        isModalOpen = true;
    }
</script>

<!-- Event List -->
<div class="max-w-2xl mx-auto my-10 space-y-4">
    <h2 class="text-3xl font-bold text-white text-center">Upcoming Events</h2>

    {#each events as event}
        <div class="bg-gray-800 text-white p-4 rounded-lg shadow-lg hover:bg-gray-700 cursor-pointer transition"
            on:click={() => openEvent(event)}
        >
            <h3 class="text-xl font-semibold">{event.name}</h3>
            <p class="text-gray-300">{event.description}</p>
            <div class="mt-2 text-gray-400">
                <span>📅 {event.event_date} | 🕒 {event.time} | 📍 {event.place}</span>
            </div>
        </div>
    {/each}
</div>

<!-- Event Modal -->
{#if isModalOpen}
    <div class="fixed inset-0 flex items-center justify-center bg-black bg-opacity-50">
        <div class="bg-white p-6 rounded-lg max-w-lg text-center">
            <h2 class="text-2xl font-bold">{selectedEvent.name}</h2>
            <p class="text-gray-600 my-2">{selectedEvent.description}</p>
            <p><strong>📅 Date:</strong> {selectedEvent.event_date}</p>
            <p><strong>🕒 Time:</strong> {selectedEvent.time}</p>
            <p><strong>📍 Place:</strong> {selectedEvent.place}</p>
            <button class="mt-4 px-4 py-2 bg-red-500 text-white rounded-md" on:click={() => isModalOpen = false}>Close</button>
        </div>
    </div>
{/if}

