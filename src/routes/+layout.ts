import { PUBLIC_SUPABASE_URL, PUBLIC_SUPABASE_ANON_KEY } from "$env/static/public";
import { createBrowserClient, isBrowser, parse } from "@supabase/ssr"
import type { LayoutLoad } from "./$types"

export const ssr = false;

export const load: LayoutLoad = async ({ fetch, data, depends }: any) => {
    depends('supabase:auth')

    const supabase = createBrowserClient(PUBLIC_SUPABASE_URL, PUBLIC_SUPABASE_ANON_KEY, {
        global: {
            fetch
        },
        cookies: {
            get(key) {
                // if server, something else
                if (!isBrowser()) {
                    return JSON.stringify(data.session);
                }

                // if we are on the browser, do something
                const cookie = parse(document.cookie);
                return cookie[key];
            },
            set(key, value) {
                document.cookie = `${key}=${value}; path=/`;
            },
            remove(key) {
                document.cookie = `${key}=; Max-Age=0; path=/`;
            }
        }
    });

    const {
        data: { session } 
    } = await supabase.auth.getSession();

    return { supabase, session }
}