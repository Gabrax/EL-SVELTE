<script lang="ts">
    import { onMount } from "svelte";
    import { page } from "$app/stores";
    export let data;

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let today = new Date();
    let currentMonth = today.getMonth();
    let currentYear = today.getFullYear();
    let daysInMonth = new Date(currentYear, currentMonth + 1, 0).getDate();
    let firstDay = new Date(currentYear, currentMonth, 1).getDay();
    let dates = [];

    onMount(() => {
        dates = Array(firstDay).fill(null).concat([...Array(daysInMonth).keys()].map(i => i + 1));
    });
    
</script>

<!-- Calendar Header -->
<div class="text-center text-white my-5">
    <h2 class="text-3xl font-bold">{today.toLocaleString('default', { month: 'long' })} {currentYear}</h2>
</div>

<!-- Calendar Grid -->
<div class="grid grid-cols-7 gap-1 max-w-lg mx-auto text-center">
    <!-- Days of the Week -->
    {#each ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"] as day}
        <div class="py-2 font-bold text-lg text-gray-300">{day}</div>
    {/each}

    <!-- Calendar Days -->
    {#each dates as day}
        <div class="w-12 h-12 flex items-center justify-center text-lg font-semibold rounded-md
            {day === today.getDate() ? 'bg-blue-600 text-white' : 'bg-gray-700 text-gray-200'}">
            {day ? day : ""}
        </div>
    {/each}
</div>
