<script lang="ts">
    import { goto } from '$app/navigation';

    export let data;
    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let email = '';
    let password = '';
    let firstName = '';
    let lastName = ''; // Updated from surname
    let organization = '';

    let isRegistering = false; // Toggle between login/register
    let errorMessage = '';

    async function handleAuth() {
        errorMessage = '';

        if (!email || !password) {
            errorMessage = "Please enter both email and password.";
            return;
        }

        if (isRegistering) {
            if (!firstName || !lastName) {
                errorMessage = "Please enter your first and last name.";
                return;
            }

            // Register user
            const { data, error } = await supabase.auth.signUp({ email, password });

            if (error) {
                errorMessage = error.message;
                return;
            }

            const userId = data.user?.id;
            if (userId) {
                // Insert into profiles table
                const { error: profileError } = await supabase
                    .from("profiles")
                    .insert([{ id: userId, first_name: firstName, last_name: lastName, organization }]);

                if (profileError) {
                    errorMessage = "Error saving profile information.";
                    return;
                }
            }
        } else {
            // Login user
            const { error } = await supabase.auth.signInWithPassword({ email, password });

            if (error) {
                errorMessage = "Invalid email or password.";
                return;
            }
        }

        // Redirect to events
        goto("/events");
    }

    // Redirect already logged-in users to /events
    $: if (session) {
        goto("/events");
    }
</script>

<div class="min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] flex items-center justify-center px-4">
    <div class="bg-[#1e293b] border border-pink-500 rounded-2xl p-8 shadow-md w-full max-w-md">
        <h1 class="text-2xl font-extrabold text-center text-pink-400 mb-6">
            {isRegistering ? "Create an Account" : "Hello There!"}
        </h1>

        {#if errorMessage}
            <p class="text-red-500 text-center mb-2">{errorMessage}</p>
        {/if}

        <div class="flex flex-col gap-4">
            <input type="email" bind:value={email} placeholder="Email" class="p-2 rounded bg-gray-800 text-white" required />
            <input type="password" bind:value={password} placeholder="Password" class="p-2 rounded bg-gray-800 text-white" required />

            {#if isRegistering}
                <input type="text" bind:value={firstName} placeholder="First Name" class="p-2 rounded bg-gray-800 text-white" required />
                <input type="text" bind:value={lastName} placeholder="Last Name" class="p-2 rounded bg-gray-800 text-white" required />
                <input type="text" bind:value={organization} placeholder="Organization (Optional)" class="p-2 rounded bg-gray-800 text-white" />
            {/if}

            <button on:click={handleAuth} class="bg-pink-500 hover:bg-pink-700 text-white font-bold py-2 px-4 rounded">
                {isRegistering ? "Register" : "Log In"}
            </button>

            <button on:click={() => isRegistering = !isRegistering} class="text-pink-400 underline text-center">
                {isRegistering ? "Already have an account? Log in" : "Don't have an account? Sign up"}
            </button>
        </div>
    </div>
</div>
