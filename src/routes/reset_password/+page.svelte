<script lang="ts">
    import { goto, invalidateAll } from "$app/navigation";
    export let data;

    let { supabase, session } = data;
    $: ({ supabase, session } = data);

    let newPassword = "";
    let message = "";
    let isSubmitting = false;

    async function updatePassword() {
        isSubmitting = true;
        message = "";

        const { error } = await supabase.auth.updateUser({
            password: newPassword
        });

        if (error) {
            message = "Error: " + error.message;
        } else {
            message = "Password updated successfully! Redirecting...";
            invalidateAll();
            setTimeout(() => goto("/"), 2000);
        }

        isSubmitting = false;
    }
</script>

<div class="hero min-h-screen bg-base-300">
    <div class="hero-content w-[500px]">
        <div class="flex flex-col items-center">
            <h2 class="text-xl font-bold mb-2">Set New Password</h2>
            <input 
                type="password" 
                bind:value={newPassword} 
                placeholder="Enter new password" 
                class="input input-bordered w-full max-w-xs"
            />
            <button 
                on:click={updatePassword} 
                class="btn btn-primary mt-2"
                disabled={isSubmitting}
            >
                {isSubmitting ? "Updating..." : "Update Password"}
            </button>
            {#if message}
                <p class="mt-2 text-sm text-gray-500">{message}</p>
            {/if}
        </div>
    </div>
</div>
