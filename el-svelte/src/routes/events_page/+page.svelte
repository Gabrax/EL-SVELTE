<script lang="ts">
  import { onMount } from 'svelte';
  import { supabase } from '../../backend/supabase';
  import { auth } from '../../backend/supabase';
  import { goto } from '$app/navigation';

  let user = null;

  // Get the user from the store
  auth.subscribe(value => {
    user = value;
    if (!user) {
      goto('/'); // Redirect to login if not authenticated
    }
  });

  async function logout() {
    await supabase.auth.signOut();
    auth.set(null);
    goto('/'); // Redirect to login
  }
</script>

<section class="main-page">
  {#if user}
    <h1>Hello, {$auth.email}!</h1>
    <button on:click={logout}>Logout</button>
  {:else}
    <p>Redirecting...</p>
  {/if}
</section>
