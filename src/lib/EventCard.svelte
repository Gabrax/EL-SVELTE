<script lang="ts">
  export let event: {
    id: number;
    name: string;
    description: string;
    date: string;
    time: string;
    location: string;
    isFavorite: boolean;
  };

  export let toggleFavorite: (id: number) => void; // Dodano typ dla funkcji toggleFavorite

  function handleToggle(): void {
    toggleFavorite(event.id); // Wywołanie funkcji nadrzędnej z ID wydarzenia
  }
</script>

<div class="group relative p-[1px] rounded-2xl bg-gradient-to-tr from-purple-500 via-pink-500 to-blue-500 transition-all duration-300 hover:scale-105 hover:shadow-2xl">
  <div class="bg-[#0f172a] rounded-2xl p-5 h-full flex flex-col justify-between">
    
    <!-- Nagłówek wydarzenia -->
    <div class="flex justify-between items-start">
      <h2 class="text-xl font-extrabold bg-gradient-to-r from-purple-400 to-blue-400 text-transparent bg-clip-text">
        {event.name}
      </h2>
      
      <!-- Przycisk do dodania do ulubionych -->
      <button 
        class={`text-gray-400 hover:text-pink-500 transition ${event.isFavorite ? 'text-pink-500' : ''}`}
        on:click={handleToggle}
        title={event.isFavorite ? 'Usuń z ulubionych' : 'Dodaj do ulubionych'}
      >
        {#if event.isFavorite}
          <i class="fa-solid fa-heart"></i> <!-- Ikona wypełnionego serca -->
        {:else}
          <i class="fa-regular fa-heart"></i> <!-- Ikona pustego serca -->
        {/if}
      </button>
    </div>

    <!-- Szczegóły wydarzenia -->
    <div class="mt-3 flex flex-wrap gap-2 text-sm">
      <span class="px-2 py-1 bg-purple-800/30 text-purple-300 rounded-full">
        📅 {event.date}
      </span>
      <span class="px-2 py-1 bg-blue-800/30 text-blue-300 rounded-full">
        📍 {event.location}
      </span>
    </div>

    <!-- Opis wydarzenia -->
    <p class="text-gray-400 mt-4 line-clamp-2">
      {event.description}
    </p>
  </div>
</div>
