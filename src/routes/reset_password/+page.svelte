<script lang="ts">
    import { goto } from "$app/navigation";
    import { page } from "$app/stores";

    // Pobranie kodu resetowania z parametru URL
    let resetCode = $page.url.searchParams.get("code");

    // Funkcja obsługująca resetowanie hasła
    function handlePasswordReset() {
        alert(`Hasło zostało zresetowane dla kodu: ${resetCode}`);
        goto("/login"); // Przekierowanie na stronę logowania po zakończeniu
    }
</script>

<div class="min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] flex items-center justify-center px-4">
    <div class="bg-[#1e293b] border border-pink-500 rounded-2xl p-8 shadow-md w-full max-w-md">
        <h1 class="text-2xl font-extrabold text-center text-pink-400 mb-6">Resetuj hasło</h1>
        <p class="text-gray-300 text-center mb-4">Wprowadź nowe hasło, aby zresetować swoje konto.</p>
        
        <!-- Formularz resetowania hasła -->
        <form on:submit|preventDefault={handlePasswordReset} class="space-y-4">
            <div>
                <label for="password" class="block text-gray-400 mb-1">Nowe hasło</label>
                <input 
                    id="password" 
                    type="password" 
                    placeholder="Wprowadź nowe hasło"
                    class="w-full px-4 py-2 rounded-md bg-[#0f172a] text-white border border-gray-600 focus:border-pink-500 focus:outline-none"
                    required
                />
            </div>
            <div>
                <label for="confirm-password" class="block text-gray-400 mb-1">Potwierdź nowe hasło</label>
                <input 
                    id="confirm-password" 
                    type="password" 
                    placeholder="Potwierdź nowe hasło"
                    class="w-full px-4 py-2 rounded-md bg-[#0f172a] text-white border border-gray-600 focus:border-pink-500 focus:outline-none"
                    required
                />
            </div>
            <button 
                type="submit"
                class="w-full px-4 py-2 bg-pink-500 hover:bg-pink-400 text-white font-bold rounded-md transition"
            >
                Resetuj hasło
            </button>
        </form>
    </div>
</div>
