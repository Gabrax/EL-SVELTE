<script lang="ts">
    export let data;
    import "../app.pcss";
    import { goto, invalidateAll } from "$app/navigation";
    import { page } from "$app/stores";
    import '@fortawesome/fontawesome-free/css/all.css';
    import '@fortawesome/fontawesome-free/js/all.js';

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let userProfile = { first_name: '', last_name: '', organization: '' };
    let isModalOpen = false;

    async function fetchUserProfile() {
        if (!session?.user) return;

        const { data, error } = await supabase
            .from("profiles")
            .select("first_name, last_name, organization")
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

    async function deleteAccount() {
        if (confirm("Are you sure you want to delete your account?")) {
            const { error } = await supabase.auth.api.deleteUser(session.user.id);
            if (error) {
                console.error("Error deleting account:", error.message);
            } else {
                await goto("/"); 
                invalidateAll();
            }
        }
    }

    async function updateProfile() {
        if (!session?.user) return;

        const { error } = await supabase
            .from("profiles")
            .upsert({
                id: session.user.id,
                first_name: userProfile.first_name,
                last_name: userProfile.last_name,
                organization: userProfile.organization
            });

        if (error) {
            console.error("Error updating profile:", error.message);
        } else {
            alert("Profile updated successfully");
            isModalOpen = false;
        }
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
        title="Settings"
        on:click={() => isModalOpen = !isModalOpen}
      >
        <i class="fas fa-cogs text-white w-6 h-6"></i>
      </button>
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

{#if isModalOpen}
  <div class="fixed inset-0 bg-black bg-opacity-50 flex justify-center items-center z-20">
    <div class="bg-white p-6 rounded-lg max-w-lg w-full space-y-4">
      <h3 class="text-xl font-semibold">Edit Profile</h3>
      <form>
        <div>
          <label class="block">First Name</label>
          <input type="text" class="w-full p-2 border" bind:value={userProfile.first_name} />
        </div>
        <div>
          <label class="block">Last Name</label>
          <input type="text" class="w-full p-2 border" bind:value={userProfile.last_name} />
        </div>
        <div>
          <label class="block">Organization</label>
          <input type="text" class="w-full p-2 border" bind:value={userProfile.organization} />
        </div>
        <div class="space-x-4 mt-4">
          <button type="button" class="p-2 bg-blue-500 text-white rounded" on:click={updateProfile}>Save</button>
          <button type="button" class="p-2 bg-gray-500 text-white rounded" on:click={() => isModalOpen = false}>Cancel</button>
        </div>
      </form>
      <div class="mt-4 space-x-4">
        <button class="p-2 bg-red-600 text-white rounded" on:click={deleteAccount}>Delete Account</button>
      </div>
    </div>
  </div>
{/if}

<slot></slot>
