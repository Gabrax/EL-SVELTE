<script lang="ts">
    export let data;
    import "../app.pcss";
    import { goto, invalidateAll } from "$app/navigation";
    import { Auth } from '@supabase/auth-ui-svelte';
    import { ThemeSupa } from '@supabase/auth-ui-shared';

    let { supabase, session } = data
    $: ({ supabase, session } = data)

    // session is null, if session is null we have no user. if its not null, we have a user

    supabase.auth.onAuthStateChange(async (event, session) => {
        if(event === "SIGNED_IN") {
            invalidateAll();
        }

        if(event === "SIGNED_OUT") {
            await goto("/");
            invalidateAll();
        }
    })

</script>

<!-- Navbar -->
<div class="bg-base-100 justify-between fixed top-0 left-0 right-0">
    <div class="navbar max-w-3xl mx-auto justify-between">
        <!--left side of navbar-->
        <div>
            <div>
                {#if session == null}
                    <a class="btn btn-ghost text-xl">Svelte Calendar</a>
                {:else}
                    <a href="/events" class="btn btn-ghost text-xl">Svelte Calendar</a>
                    <a href="/calendar" class="btn btn-ghost">My Events</a>
                {/if}
            </div>
        </div>
        <!--right side of navbar-->
        <div>
            {#if session == null}
                
            {:else}
                <span class="text-white text-lg ml-2">{session.user.email}</span>
                <button class="ml-2" on:click={async () => { await supabase.auth.signOut()}}>Logout</button>
            {/if}
        </div>
    </div>
</div>

<slot></slot>
