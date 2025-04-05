<script lang="ts">
    export let data;
    import { Auth } from '@supabase/auth-ui-svelte';
    import { ThemeSupa } from '@supabase/auth-ui-shared';
    import { goto } from '$app/navigation';

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    console.log(supabase);
    console.log(session);

    $: if (session) {
        goto("/events");
    }
</script>

<div class="min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] flex items-center justify-center px-4">
    <div class="bg-[#1e293b] border border-pink-500 rounded-2xl p-8 shadow-md w-full max-w-md">
        <h1 class="text-2xl font-extrabold text-center text-pink-400 mb-6">Welcome to Svelte Calendar</h1>
        <p class="text-gray-300 text-center mb-4">Create an account or login below!</p>
        <Auth 
            supabaseClient={supabase}
            theme="dark"
            appearance={{
                theme: ThemeSupa,
                style: {
                    input: "width: 100%; padding: 0.5rem; border-radius: 0.375rem; background-color: #0f172a; color: #ffffff;",
                    button: "background-color: #9333ea; color: #ffffff; padding: 0.5rem 1rem; border-radius: 0.375rem; font-weight: bold;",
                    container: "gap: 1rem;"
                }
            }}
            providers={['facebook', 'twitter']}
        />
    </div>
</div>
