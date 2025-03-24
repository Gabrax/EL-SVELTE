<script lang="ts">
    import { page } from "$app/stores";
    export let data;

    let { supabase, session } = data;
    $: ({ supabase, session } = data);
    $: email = $page.params.email;

    let profile: any = {
        description: "This is your description, feel free to write about yourself.",
        pokemon_ids: []
    };
    let isModalOpen = false;

    async function saveProfile() {
        const { data: profileData, error: profileError } = await supabase.from("profiles").select("*").eq('email', email);

        if (profileData?.length === 0) { // create a new row
            const { data, error } = await supabase
                .from("profiles")
                .insert({ ...profile, user_id: session?.user?.id, email: session?.user?.email });
        } else { // update the profile row
            const { data, error } = await supabase
                .from("profiles")
                .update(profile) // description
                .eq("user_id", session?.user?.id);
        }
    }

    page.subscribe(async () => {
        // Try to grab the current profile (email)
        const { data: profileData, error: profileError } = await supabase.from("profiles").select("description").eq('email', email);
        console.log(email);
        console.log(session?.user?.email);
        console.log(profileData);

        if (profileData?.length == 0 && email == session?.user?.email) {
            // saveProfile
            console.log("SAVE PROFILE");
            await saveProfile();
        } else if (profileData != null && profileData.length > 0) {
            profile = profileData[0];
        } else {
            console.log("NO PROFILE");
            profile = {
                description: "This user does not have a profile yet!",
                pokemon_ids: []
            };
        }
    });

    async function savePageEdits() {
        await saveProfile();
        isModalOpen = false;
    }

</script>

<div class="hero min-h-screen bg-base-300">
    <div class="hero-content">
        <div class="max-w-2xl text-center">
            <h1 class="text-white font-bold text-4xl">{email}'s Page</h1>
            <p class="py-3 max-w-md mx-auto">{profile.description}</p>
            {#if email == session?.user?.email}
                <button class="btn btn-info" on:click={() => isModalOpen = true}>Edit Page</button>
                <dialog class="modal min-w-lg" class:modal-open={isModalOpen}>
                    <div class="modal-box">
                        <h3>Edit Your Profile</h3>
                        <p>Here you can make edits to your profile description.</p>
                        <p class="text-white p-2">Edit your description</p>
                        <textarea 
                            bind:value={profile.description} 
                            class="textarea textarea-bordered textarea-lg w-full max-w-md h-[300px]"
                        />
                        <button class="btn btn-success" on:click={() => savePageEdits()}>Save Edits</button>
                    </div>
                </dialog>
            {/if}
        </div>
    </div>
</div>
