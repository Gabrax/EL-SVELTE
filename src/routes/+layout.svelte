<script lang="ts">
  export let data;
  import "../app.pcss";
  import { goto, invalidateAll } from "$app/navigation";
  import { page } from "$app/stores";
  import "@fortawesome/fontawesome-free/css/all.css";
  import "@fortawesome/fontawesome-free/js/all.js";

  let { supabase, session } = data;
  $: ({ supabase, session } = data);

  let userProfile = { first_name: "", last_name: "", organization: "" };
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
    const { error } = await supabase.from("profiles").upsert({
      id: session.user.id,
      first_name: userProfile.first_name,
      last_name: userProfile.last_name,
      organization: userProfile.organization,
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

  $: currentPath = $page?.url?.pathname || "";
</script>

{#if !currentPath.startsWith("/reset_password")}
  <nav
    class="bg-gradient-to-r from-[#0f172a] to-[#111827] fixed top-0 left-0 right-0 border-b border-pink-500 z-10 w-full"
  >
    <div class="flex justify-between items-center w-full px-8 py-3">
      <!-- Left side of navbar -->
      <div class="flex items-center space-x-2">
        <img src="/logo.svg" alt="Logo" class="w-12 h-12" />
        <a
          href="/"
          class="text-pink-400 text-xl font-bold hover:text-pink-300 transition"
          >Svelte Calendar</a
        >
        {#if session}
          <a
            href="/calendar"
            class="text-white text-lg hover:text-pink-400 transition"
            >My Events</a
          >
        {/if}
      </div>

      <!-- Right side of navbar -->
      <div class="flex items-center space-x-2">
        {#if session}
          <span class="text-white text-lg">
            {#if userProfile.first_name && userProfile.last_name}
              {userProfile.first_name} {userProfile.last_name}
            {:else}
              {session.user.email}
            {/if}
          </span>
          <button
            class="p-2 rounded-full bg-gray-700 hover:bg-gray-600 focus:outline-none transition"
            title="Settings"
            on:click={() => (isModalOpen = !isModalOpen)}
          >
            <i class="fas fa-cogs text-white w-6 h-6"></i>
          </button>
          <button
            class="p-2 rounded-full bg-gray-700 hover:bg-gray-600 focus:outline-none transition"
            title="Logout"
            on:click={handleLogout}
          >
            <svg
              xmlns="http://www.w3.org/2000/svg"
              fill="none"
              viewBox="0 0 24 24"
              stroke-width="1.5"
              stroke="currentColor"
              class="w-6 h-6 text-white"
            >
              <path
                stroke-linecap="round"
                stroke-linejoin="round"
                d="M15.75 9V5.25A2.25 2.25 0 0013.5 3h-6a2.25 2.25 0 00-2.25 2.25v13.5A2.25 2.25 0 007.5 21h6a2.25 2.25 0 002.25-2.25V15M9 12h12m0 0l-3-3m3 3l-3 3"
              />
            </svg>
          </button>
        {:else}
          <button
            class="p-2 rounded-full bg-gray-700 hover:bg-gray-600 focus:outline-none transition"
            title="Login"
            on:click={() => goto("/login")}
          >
            <svg
              xmlns="http://www.w3.org/2000/svg"
              width="24"
              height="24"
              viewBox="0 0 24 24"
            >
              <g
                fill="none"
                stroke="#fff"
                stroke-linecap="round"
                stroke-linejoin="round"
                stroke-width="2"
              >
                <path
                  d="M15 8V6a2 2 0 0 0-2-2H6a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h7a2 2 0 0 0 2-2v-2"
                />
                <path d="M21 12H8l3-3m0 6l-3-3" />
              </g>
            </svg>
          </button>
        {/if}
      </div>
    </div>
  </nav>
{/if}

{#if isModalOpen}
  <div
    class="fixed inset-0 bg-black bg-opacity-50 flex justify-center items-center z-20"
  >
    <div
      class="bg-gray-900 p-6 rounded-lg shadow-lg w-[90%] max-w-md text-white relative"
    >
      <h3 class="text-xl font-bold mb-4 text-center">Edytuj Profil</h3>
      <form>
        <div class="mb-4">
          <label class="block">Imię</label>
          <input
            type="text"
            class="p-2 rounded bg-gray-800 text-white w-full"
            bind:value={userProfile.first_name}
          />
        </div>
        <div class="mb-4">
          <label class="block">Nazwisko</label>
          <input
            type="text"
            class="p-2 rounded bg-gray-800 text-white w-full"
            bind:value={userProfile.last_name}
          />
        </div>
        <div class="mb-4">
          <label class="block">Organizacja</label>
          <input
            type="text"
            class="p-2 rounded bg-gray-800 text-white w-full"
            bind:value={userProfile.organization}
          />
        </div>
        <div class="flex justify-between mt-6">
          <div>
            <button
              class="bg-red-600 hover:bg-red-800 text-white font-bold py-2 px-4 rounded mt-2"
              on:click={deleteAccount}>Usuń konto</button
            >
          </div>
          <div class="space-x-4 mt-2">
            <button
              type="button"
              class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded"
              on:click={updateProfile}>Zapisz</button
            >
            <button
              type="button"
              class="bg-gray-500 hover:bg-gray-700 text-white font-bold py-2 px-4 rounded"
              on:click={() => (isModalOpen = false)}>Anuluj</button
            >
          </div>
        </div>
      </form>
    </div>
  </div>
{/if}

<slot></slot>
