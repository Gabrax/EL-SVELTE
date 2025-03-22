
<script lang="ts">
	import { onMount } from 'svelte';

  import { supabase } from '../backend/supabase';
	let isLogin = true;

	function toggleMode() {
		isLogin = !isLogin;
	}

	function handleSubmit(event: Event) {
		event.preventDefault();
		const formData = new FormData(event.target as HTMLFormElement);
		const data = Object.fromEntries(formData.entries());
		console.log(isLogin ? 'Logging in with' : 'Registering with', data);
	}
</script>

<svelte:head>
	<title>{isLogin ? 'Login' : 'Register'}</title>
	<meta name="description" content="User authentication" />
</svelte:head>

<section class="auth-container">
	<h1>{isLogin ? 'Login' : 'Register'}</h1>
	<form on:submit={handleSubmit}>
		{#if !isLogin}
			<div>
				<label for="username">Username</label>
				<input type="text" id="username" name="username" required />
			</div>
		{/if}
		<div>
			<label for="email">Email</label>
			<input type="email" id="email" name="email" required />
		</div>
		<div>
			<label for="password">Password</label>
			<input type="password" id="password" name="password" required />
		</div>
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

	p {
		margin-top: 1rem;
	}

	a {
		color: #ff3e00;
		cursor: pointer;
		text-decoration: none;
	}
</style>

