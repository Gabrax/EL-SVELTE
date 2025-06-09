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
    attendeesCount: number; // na razie na sztywno, później można podmienić
    attendeesLimit: number; // na razie na sztywno, później można podmienić
  };

  export let subevents_count: number;
  export let toggleFavorite: (id: number) => void;
  export let onEdit: (updatedEvent: typeof event) => void; // Pass the full updated event
  export let currentUserId: number; // The logged-in user's ID
  export let deleteEvent: (id: number) => void; // Function to handle event deletion
  let isFavorite = event.isFavorite;
  let unlikeAnimating = false;


  let isModalOpen = false;
  let updatedEvent = { ...event };

  // Format date
  function formatDateTime(dateString: string): string {
    if (!dateString) return "";
    const date = new Date(dateString);
    return date.toLocaleString("pl-PL", {
      year: "numeric",
      month: "long",
      day: "numeric",
      hour: "2-digit",
      minute: "2-digit",
    });
  }

  //sprawdzanie, czy wydarzenie już się odbyło
  function isPastEvent(endDate: string): boolean {
    return new Date(endDate) < new Date();
  }

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
    onEdit(updatedEvent);
    closeModal();
  }

  // Handle event deletion
  function handleDelete() {
    deleteEvent(event.id);
    closeModal();
  }

  // Handle toggling favorite
function handleToggle(): void {
  if (isFavorite) {
    unlikeAnimating = true;
    setTimeout(() => {
      unlikeAnimating = false;
      isFavorite = !isFavorite;
      toggleFavorite(event.id);
    }, 400); // czas animacji
  } else {
    isFavorite = !isFavorite;
    toggleFavorite(event.id);
  }
}


  // Format subevents text based on count
  function formatSubeventsText(count: number): string {
  if (count === 0) return "Brak wydarzeń podczas konferencji";
  if (count === 1) return "1 wydarzenie podczas konferencji";
  if (count >= 2 && count <= 4) return `${count} wydarzenia podczas konferencji`;
  return `${count} wydarzeń podczas konferencji`;
  }
</script>

<div
class={`group relative p-[1px] rounded-2xl bg-gradient-to-tr from-purple-500 via-pink-500 to-blue-500 transition-all duration-300 hover:scale-105 hover:shadow-2xl ${isPastEvent(event.end_date) ? 'opacity-50' : ''}`}
>
  <div
    class="bg-[#0f172a] rounded-2xl pt-2 pb-5 px-5 h-full flex flex-col justify-between"
  >
    <!-- Event Header -->
    <div class="flex justify-between items-start">
      <h3 class="text-lg font-bold text-white mb-2">{event.title}</h3>
      <p class="text-sm text-gray-400 mt-1">{formatSubeventsText(subevents_count)}</p>
      {#if currentUserId}
        <!-- Favorite Button -->
        <div class="relative">
      {#if isFavorite}
  <button
    class={`text-gray-400 hover:text-pink-500 ${unlikeAnimating ? 'unlike-animation' : 'heart-icon'}`}
    on:click={(event) => { event.stopPropagation(); handleToggle(); }}
    title="Remove from favorites"
  >
    <i class="fa-solid fa-heart text-pink-500"></i>
  </button>
{:else}
  <button
    class="text-gray-400 hover:text-pink-500"
    on:click={(event) => { event.stopPropagation(); handleToggle(); }}
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
            <i class="fa-solid fa-edit"></i>
          </button>
        {/if}
      {/if}
    </div>

    <!-- Event Details -->
    <div class="mt-3 flex flex-wrap gap-2 text-sm">
      <span class="px-2 py-1 bg-purple-800/30 text-purple-300 rounded-full">
        📅 {formatDateTime(event.start_date)} - {formatDateTime(event.end_date)}
      </span>
      <span class="px-2 py-1 bg-blue-800/30 text-blue-300 rounded-full">
        📍 {event.location}
      </span>
      <span class="px-2 py-1 bg-green-800/30 text-green-300 rounded-full">
        🏛 {event.venue}
      </span>
    </div>

    <!-- New: Attendees Count (podmienić ilość uczestników) --> 
    <p class="text-sm text-gray-300 mt-4">Zapisani uczestnicy: {event.attendeesCount}/{event.attendeesLimit}</p>

    <!-- Event Description -->
    <p class="text-gray-400 mt-4 line-clamp-2">
      {event.description}
    </p>
  </div>
</div>

<!-- Modal for Editing or Deleting -->
{#if isModalOpen}
  <div
    class="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50"
  >
    <div class="bg-white rounded-lg p-6 w-96">
      <h3 class="text-xl font-bold mb-4">Edit Event</h3>

      <form>
        <div class="mb-4">
          <label
            for="event-title"
            class="block text-sm font-medium text-gray-700">Title</label
          >
          <input
            id="event-title"
            type="text"
            bind:value={updatedEvent.title}
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label
            for="event-description"
            class="block text-sm font-medium text-gray-700">Description</label
          >
          <textarea
            id="event-description"
            bind:value={updatedEvent.description}
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          ></textarea>
        </div>

        <div class="mb-4">
          <label
            for="start-date"
            class="block text-sm font-medium text-gray-700">Start Date</label
          >
          <input
            id="start-date"
            type="date"
            bind:value={updatedEvent.start_date}
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label for="end-date" class="block text-sm font-medium text-gray-700"
            >End Date</label
          >
          <input
            id="end-date"
            type="date"
            bind:value={updatedEvent.end_date}
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label
            for="event-location"
            class="block text-sm font-medium text-gray-700"
          >
            Location
          </label>
          <input
            id="event-location"
            type="text"
            bind:value={updatedEvent.location}
            class="mt-1 p-2 w-full border rounded bg-gray-100"
          />
        </div>

        <div class="mb-4">
          <label
            for="event-venue"
            class="block text-sm font-medium text-gray-700"
          >
            Venue
          </label>
          <input
            id="event-venue"
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

  @keyframes heart-unlike {
    0% {
      transform: scale(1);
      opacity: 1;
    }
    50% {
      transform: scale(0.6);
      opacity: 0.5;
    }
    100% {
      transform: scale(1);
      opacity: 0;
    }
  }

  .heart-icon {
    animation: heart-pulse 0.6s ease-in-out;
  }

  .unlike-animation {
    animation: heart-unlike 0.4s ease-in-out forwards;
  }
</style>

