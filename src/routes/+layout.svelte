<script lang="ts">
    export let data;
    import "../app.pcss";
    import { goto, invalidateAll } from "$app/navigation";
    import { page } from "$app/stores";
    import '@fortawesome/fontawesome-free/css/all.css';
    import '@fortawesome/fontawesome-free/js/all.js';

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let userProfile = { first_name: '', last_name: '' };

    async function fetchUserProfile() {
        if (!session?.user) return;

        const { data, error } = await supabase
            .from("profiles")
            .select("first_name, last_name")
            .eq("id", session.user.id)
            .single();

        if (error) {
            console.error("Error fetching profile:", error.message);
            return;
        }

        if (data) {
            userProfile = data;
        }
    }

    async function handleLogout() {
        await supabase.auth.signOut();
    }

    supabase.auth.onAuthStateChange(async (event, session) => {
        if (event === "SIGNED_IN") {
            await fetchUserProfile();
            invalidateAll();
        }

        if (event === "SIGNED_OUT") {
            await goto("/");
            invalidateAll();
        }
    });

    if (session) {
        fetchUserProfile();
    }

    $: currentPath = $page?.url?.pathname || '';
</script>

{#if currentPath !== '/' && !currentPath.startsWith('/reset_password')}
<nav class="bg-gradient-to-r from-[#0f172a] to-[#111827] fixed top-0 left-0 right-0 border-b border-pink-500 z-10">
  <div class="navbar max-w-7xl mx-auto px-6 py-3 flex justify-between items-center">
    <!-- Left side of navbar -->
    <div class="flex items-center space-x-4">
      <a href="/events" class="text-pink-400 text-xl font-bold hover:text-pink-300 transition">Svelte Calendar</a>
      <a href="/calendar" class="text-white text-lg hover:text-pink-400 transition">My Events</a>
    </div>

    <!-- Right side of navbar -->
    <div class="flex items-center space-x-4">
      <span class="text-white text-lg">
        {#if userProfile.first_name && userProfile.last_name}
          {userProfile.first_name} {userProfile.last_name}
        {:else}
          {session?.user.email}  <!-- Fallback to email if no profile data -->
        {/if}
      </span>
      <button 
        class="p-2 rounded-full bg-gray-700 hover:bg-gray-600 focus:outline-none transition" 
        title="Logout"
        on:click={handleLogout}
      >
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6 text-white">
          <path stroke-linecap="round" stroke-linejoin="round" d="M15.75 9V5.25A2.25 2.25 0 0013.5 3h-6a2.25 2.25 0 00-2.25 2.25v13.5A2.25 2.25 0 007.5 21h6a2.25 2.25 0 002.25-2.25V15M9 12h12m0 0l-3-3m3 3l-3 3"/>
        </svg>
      </button>
    </div>
  </div>
</nav>
{/if}

<slot></slot>
