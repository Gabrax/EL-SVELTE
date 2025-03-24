<script lang="ts">
  import { onMount } from 'svelte';
  import { supabase } from '../backend/supabase';
  import { auth } from '../backend/supabase';
  import { goto } from '$app/navigation';
  import { writable } from 'svelte/store';

  let isLogin = true;
  let message = writable('');

  function toggleMode() {
    isLogin = !isLogin;
    message.set('');
  }

  async function handleSubmit(event: Event) {
    event.preventDefault();
    const formData = new FormData(event.target as HTMLFormElement);
    const data = Object.fromEntries(formData.entries());

    let response;
    if (isLogin) {
      response = await supabase.auth.signInWithPassword({
        email: data.email as string,
        password: data.password as string
      });
    } else {
      response = await supabase.auth.signUp({
        email: data.email as string,
        password: data.password as string
      });
    }

    if (response.error) {
      message.set(response.error.message);
    } else {
      auth.set(response.data.user); // Save user data
      goto('/events_page'); // Redirect to main page
    }
  }
</script>

<section class="auth-container">
  <h1>{isLogin ? 'Login' : 'Register'}</h1>
  {#if $message}
    <p class="message">{$message}</p>
  {/if}
  <form on:submit={handleSubmit}>
    <div>
      <label for="email">Email</label>
      <input type="email" id="email" name="email" required />
    </div>
    <div>
      <label for="password">Password</label>
      <input type="password" id="password" name="password" required 
        pattern="^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&amp;]).*$"
        minlength="8"
        title="Hasło musi mieć co najmniej 8 znaków, zawierać jedną wielką literę, jedną cyfrę i jeden znak specjalny." />    </div>
    <button type="submit">{isLogin ? 'Login' : 'Register'}</button>
  </form>
  <p>
    {isLogin ? "Don't have an account?" : "Already have an account?"}
    <a href="#" on:click|preventDefault={toggleMode}>{isLogin ? 'Register' : 'Login'}</a>
  </p>
</section>

<style>
	.auth-container {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
		padding: 2rem;
		max-width: 400px;
		margin: auto;
		box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1);
		border-radius: 8px;
	}

	.message {
		color: red;
		font-size: 0.9rem;
		margin-bottom: 1rem;
	}

	form {
		width: 100%;
		display: flex;
		flex-direction: column;
	}

	div {
		margin-bottom: 1rem;
	}

	label {
		font-weight: bold;
		margin-bottom: 0.5rem;
		display: block;
	}

	input {
		width: 100%;
		padding: 0.5rem;
		border: 1px solid #ccc;
		border-radius: 4px;
	}

	button {
		background-color: #ff3e00;
		color: white;
		border: none;
		padding: 0.75rem;
		border-radius: 4px;
		cursor: pointer;
		font-size: 1rem;
	}

	button:hover {
		background-color: #e63a00;
	}

	.oauth-buttons {
		display: flex;
		gap: 0.5rem;
		justify-content: center;
		margin-top: 1rem;
	}

	.oauth-btn {
		background: white;
		border: none;
		border-radius: 50%;
		width: 40px;
		height: 40px;
		display: flex;
		align-items: center;
		justify-content: center;
		cursor: pointer;
		box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);
		font-size: 20px;
	}

	.oauth-btn i {
		color: #333;
	}

	.oauth-btn:hover {
		opacity: 0.8;
	}

	p {
		margin-top: 1rem;
	}

	a {
		color: #ff3e00;
		cursor: pointer;
		text-decoration: none;
	}
</style>
