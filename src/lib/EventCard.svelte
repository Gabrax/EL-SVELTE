<script lang="ts">
  export let event: {
    id: number;
    user_id: number;
    title: string;
    description: string;
    start_date: string;
    end_date: string;
    location: string;
    venue: string;
    isFavorite: boolean;
  };

  export let toggleFavorite: (id: number) => void;
  export let onEdit: (id: number) => void; // Function to handle the edit event
  export let currentUserId: number; // The logged-in user's ID
  export let deleteEvent: (id: number) => void; // Function to handle event deletion
  let isFavorite = event.isFavorite; 

  let isModalOpen = false;
  let updatedEvent = { ...event };

  // Open and close the modal
  function openModal() {
    updatedEvent = { ...event }; // Reset to current event values
    isModalOpen = true;
  }

  function closeModal() {
    isModalOpen = false;
  }

  // Handle event update
  function handleSave() {
    // Logic to save the edited event data
    // Call your event update function here, passing `updatedEvent`
    onEdit(updatedEvent);
    closeModal();
  }

  // Handle event deletion
  function handleDelete() {
    // Logic to delete the event
    deleteEvent(event.id);
    closeModal();
  }

  // Handle toggling favorite
  function handleToggle(): void {
  isFavorite = !isFavorite; 
  toggleFavorite(event.id); 
}
</script>

<style>
  @keyframes heart-pulse {
    0% {
      transform: scale(1);
    }
    50% {
      transform: scale(1.5);
    }
    100% {
      transform: scale(1);
    }
  }

  .heart-icon {
    animation: heart-pulse 0.6s ease-in-out;
  }
</style>

<div class="group relative p-[1px] rounded-2xl bg-gradient-to-tr from-purple-500 via-pink-500 to-blue-500 transition-all duration-300 hover:scale-105 hover:shadow-2xl">
  <div class="bg-[#0f172a] rounded-2xl p-5 h-full flex flex-col justify-between">
    
    <!-- Event Header -->
    <div class="flex justify-between items-start">
      <h2 class="text-xl font-extrabold bg-gradient-to-r from-purple-400 to-blue-400 text-transparent bg-clip-text">
        {event.title}
      </h2>
      
      <!-- Favorite Button -->
   <div class="relative">
  {#if isFavorite}
    <button 
      class="text-gray-400 hover:text-pink-500 heart-icon"
      on:click={handleToggle}
      title="Remove from favorites"
    >
      <i class="fa-solid fa-heart text-pink-500"></i> 
    </button>
  {:else}
    <button 
      class="text-gray-400 hover:text-pink-500 "
      on:click={handleToggle}
      title="Add to favorites"
    >
      <i class="fa-regular fa-heart"></i> 
    </button>
  {/if}
</div>

      <!-- Edit Button (Visible only if the current user is the event creator) -->
      {#if event.user_id === currentUserId}
        <button 
          class="text-gray-400 hover:text-blue-500 transition"
          on:click={openModal}
          title="Edit event"
        >
          <i class="fa-solid fa-edit"></i>  <!-- Pencil icon for editing -->
        </button>
      {/if}
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

<!-- Modal for Editing or Deleting -->
{#if isModalOpen}
  <div class="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50">
    <div class="bg-white rounded-lg p-6 w-96">
      <h3 class="text-xl font-bold mb-4">Edit Event</h3>

      <form>
        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">Title</label>
          <input 
            type="text" 
            bind:value={updatedEvent.title} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">Description</label>
          <textarea 
            bind:value={updatedEvent.description} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          ></textarea>
        </div>

        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">Start Date</label>
          <input 
            type="date" 
            bind:value={updatedEvent.start_date} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">End Date</label>
          <input 
            type="date" 
            bind:value={updatedEvent.end_date} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">Location</label>
          <input 
            type="text" 
            bind:value={updatedEvent.location} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label class="block text-sm font-medium text-gray-700">Venue</label>
          <input 
            type="text" 
            bind:value={updatedEvent.venue} 
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <!-- Action Buttons -->
        <div class="flex justify-between mt-6">
          <button 
            type="button" 
            on:click={handleSave} 
            class="bg-blue-500 text-white px-4 py-2 rounded"
          >
            Save
          </button>
          <button 
            type="button" 
            on:click={handleDelete} 
            class="bg-red-500 text-white px-4 py-2 rounded"
          >
            Delete
          </button>
          <button 
            type="button" 
            on:click={closeModal} 
            class="bg-gray-300 text-black px-4 py-2 rounded"
          >
            Cancel
          </button>
        </div>
      </form>
    </div>
  </div>
{/if}