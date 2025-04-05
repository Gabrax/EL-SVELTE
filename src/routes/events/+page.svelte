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

  export const events = [
      {
        id: 1,
        name: "Svelte Conf 2025",
        description: "Największa konferencja Svelte na świecie!",
        date: "2025-07-20",
        time: "10:00",
        location: "Berlin, Niemcy",
        isFavorite: false,
      },
      {
        id: 2,
        name: "Frontend Fest",
        description: "Spotkanie frontendowców z całej Europy",
        date: "2025-06-15",
        time: "14:00",
        location: "Warszawa, Polska",
        isFavorite: false,
      },
      {
        id: 3,
        name: "Open Source Meetup",
        description: "Prezentacje i networking dla fanów open source.",
        date: "2025-08-01",
        time: "18:00",
        location: "Kraków, Polska",
        isFavorite: false,
      },
      {
        id: 4,
        name: "Hackathon AI",
        description: "48h kodowania z użyciem AI — wygraj nagrody!",
        date: "2025-09-10",
        time: "09:00",
        location: "Online",
        isFavorite: false,
      },
      {
        id: 5,
        name: "Tech Talks Poznań",
        description: "Prelekcje i networking z lokalną sceną IT",
        date: "2025-05-30",
        time: "17:30",
        location: "Poznań, Polska",
        isFavorite: true,
      },
      {
        id: 6,
        name: "React Europe",
        description: "Wydarzenie dla fanów Reacta i frontendu",
        date: "2025-07-01",
        time: "11:00",
        location: "Paryż, Francja",
        isFavorite: false,
      },
      {
        id: 7,
        name: "Code Camp 2025",
        description: "Tygodniowy bootcamp z najlepszymi mentorami",
        date: "2025-08-20",
        time: "09:00",
        location: "Zakopane, Polska",
        isFavorite: false,
      },
      {
        id: 8,
        name: "JavaScript Picnic",
        description: "Luzne spotkanie devów JS + grill 🍔",
        date: "2025-06-10",
        time: "16:00",
        location: "Gdańsk, Polska",
        isFavorite: true,
      },
      {
        id: 9,
        name: "UX/UI Design Night",
        description: "Inspirujące case studies i design talki",
        date: "2025-07-12",
        time: "18:00",
        location: "Wrocław, Polska",
        isFavorite:false
      },
    {
        id: 10,
        name: "CyberSec Forum",
        description: "Cyberbezpieczeństwo w praktyce – prelekcje + warsztaty",
        date: "2025-10-05",
        time: "10:00",
        location: "Online",
        isFavorite:false
    }
        ];

        // Funkcja do obsługi ulubionych
  function toggleFavorite(eventId: number): void { // Dodano typ `number` dla eventId
    const event = events.find(e => e.id === eventId);
    if (event) {
      event.isFavorite = !event.isFavorite; // Zmiana stanu ulubionych
    }
  }
</script>
  
  <div class="w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 space-y-6 overflow-x-hidden">
    <h2 class="text-3xl font-bold text-pink-400 text-center">Wydarzenia</h2>
    
    <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8 px-6">
      {#each events as event}
        <div class="hover:shadow-lg transition">
          <!-- Przekazanie funkcji toggleFavorite do komponentu EventCard -->
          <EventCard {event} {toggleFavorite} />
        </div>
      {/each}
    </div>
  </div>
  

  