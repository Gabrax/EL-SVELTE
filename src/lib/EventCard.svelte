<script lang="ts">
  export let event: {
    id: number;
    title: string;
    description: string;
    start_date: string;
    end_date: string;
    location: string;
    venue: string;
    isFavorite: boolean;
  };

  export let toggleFavorite: (id: number) => void;

  function handleToggle(): void {
    toggleFavorite(event.id);
  }
</script>

<div class="group relative p-[1px] rounded-2xl bg-gradient-to-tr from-purple-500 via-pink-500 to-blue-500 transition-all duration-300 hover:scale-105 hover:shadow-2xl">
  <div class="bg-[#0f172a] rounded-2xl p-5 h-full flex flex-col justify-between">
    
    <!-- Event Header -->
    <div class="flex justify-between items-start">
      <h2 class="text-xl font-extrabold bg-gradient-to-r from-purple-400 to-blue-400 text-transparent bg-clip-text">
        {event.title}
      </h2>
      
      <!-- Favorite Button -->
      <button 
        class={`text-gray-400 hover:text-pink-500 transition ${event.isFavorite ? 'text-pink-500' : ''}`}
        on:click={handleToggle}
        title={event.isFavorite ? 'Remove from favorites' : 'Add to favorites'}
      >
        {#if event.isFavorite}
          <i class="fa-solid fa-heart"></i>
        {:else}
          <i class="fa-regular fa-heart"></i>
        {/if}
      </button>
    </div>

    <!-- Event Details -->
    <div class="mt-3 flex flex-wrap gap-2 text-sm">
      <span class="px-2 py-1 bg-purple-800/30 text-purple-300 rounded-full">
        📅 {event.start_date} - {event.end_date}
      </span>
      <span class="px-2 py-1 bg-blue-800/30 text-blue-300 rounded-full">
        📍 {event.location}
      </span>
      <span class="px-2 py-1 bg-green-800/30 text-green-300 rounded-full">
        🏛 {event.venue}
      </span>
    </div>

    <!-- Event Description -->
    <p class="text-gray-400 mt-4 line-clamp-2">
      {event.description}
    </p>
  </div>
</div>

