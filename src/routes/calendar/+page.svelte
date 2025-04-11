<script lang="ts">
    import { onMount } from "svelte";

    export let data;
    let { supabase, session } = data;

    type Event = {
        id: number;
        title: string;
        description: string;
        start_date: string;
        end_date: string;
        location: string;
        venue: string;
        isFavorite: boolean;
        video_link?: string; // Add video_link as an optional field
    };

    type CalendarDay = {
        day: number;
        weekday: string;
        events: Event[];
        date: Date;
    };

    let events: Event[] = [];
    let today = new Date();
    let currentMonth = today.getMonth();
    let currentYear = today.getFullYear();
    let dates: CalendarDay[] = [];
    let hoveredEvents: Event[] = [];
    let showPopup = false;
    let isMinimized = false;
    let popupPosition = { x: 0, y: 0 }; // For tracking position of the popup
    let dragging = false;
    let dragOffset = { x: 0, y: 0 }; // Offset for dragging
    let videoUrl: string = '';


    let months = Array.from({ length: 12 }, (_, i) =>
        new Date(currentYear, i).toLocaleString("default", { month: "long" })
    );

    async function fetchFavoriteEvents() {
        if (!session?.user?.id) return;

        try {
            // Fetch favorite conference IDs for the user
            let { data: participantData, error } = await supabase
                .from("conference_participants")
                .select("conference_id")
                .eq("user_id", session.user.id)
                .eq("is_favourited", true);

            if (error) throw error;

            if (participantData.length === 0) {
                console.log("No favorite events found.");
                return;
            }

            const conferenceIds = participantData.map(p => p.conference_id);

            // Fetch event details from conferences table, including the video_link
            let { data: conferenceData, error: confError } = await supabase
                .from("conferences")
                .select("*")  // Ensure you're selecting the video_link column as well
                .in("id", conferenceIds);

            if (confError) throw confError;

            // Update events array to include video_link
            events = conferenceData.map(conf => ({
                id: conf.id,
                title: conf.title,
                description: conf.description,
                start_date: conf.start_date,
                end_date: conf.end_date,
                location: conf.location,
                venue: conf.venue,
                isFavorite: true,
                video_link: conf.video_link // Store the video_link here
            }));

            dates = generateDates(currentYear, currentMonth);
        } catch (err) {
            console.error("Error fetching favorite events:", err);
        }
    }

    function generateDates(year: number, month: number): CalendarDay[] {
        const daysInMonth = new Date(year, month + 1, 0).getDate();
        const weekdays = ["Nd", "Pn", "Wt", "Śr", "Cz", "Pt", "Sb"];

        return Array.from({ length: daysInMonth }, (_, i) => {
            const date = new Date(year, month, i + 1);
            return {
                day: i + 1,
                date,
                weekday: weekdays[date.getDay()],
                events: getEventsForDay(i + 1),
            };
        });
    }

    function getEventsForDay(day: number): Event[] {
        return events.filter(event => {
            const eventDate = new Date(event.start_date);
            return (
                eventDate.getDate() === day &&
                eventDate.getMonth() === currentMonth &&
                eventDate.getFullYear() === currentYear
            );
        });
    }

    function isPastDay(day: number): boolean {
        const date = new Date(currentYear, currentMonth, day);
        return date < new Date(today.getFullYear(), today.getMonth(), today.getDate());
    }

    function changeMonth(direction: number): void {
        currentMonth += direction;
        if (currentMonth < 0) {
            currentMonth = 11;
            currentYear--;
        } else if (currentMonth > 11) {
            currentMonth = 0;
            currentYear++;
        }
        dates = generateDates(currentYear, currentMonth);
    }

    // Fetch events when the component mounts
    onMount(fetchFavoriteEvents);
    $: favoriteEvents = events.filter(event => event.isFavorite);
    $: myEvents = events;

    // Function to handle click on a day
    function handleDayClick(events: Event[]): void {
        hoveredEvents = events;
    }

    function handleWatchButtonClick(event: Event): void {
        showPopup = true;
        if (event.video_link) {
            // Check if video_link is a valid YouTube URL and append autoplay=1
            let url = new URL(event.video_link);
            if (!url.searchParams.has('autoplay')) {
                url.searchParams.set('autoplay', '1'); // Add autoplay parameter
            }
            videoUrl = url.toString(); // Set videoUrl with autoplay
        }
    }

    // Close the popup
    function closePopup(event: MouseEvent): void {
        // Prevent close if the click is inside the popup
        event.stopPropagation();
        showPopup = false;
        isMinimized = false;
    }

    function minimizePopup(): void {
        isMinimized = !isMinimized;
    }

    function restorePopup(): void {
        isMinimized = false;
    }

    // Start dragging the popup
    function startDrag(event: MouseEvent): void {
        dragging = true;
        dragOffset = {
            x: event.clientX - popupPosition.x,
            y: event.clientY - popupPosition.y
        };
        document.addEventListener("mousemove", handleDrag);
        document.addEventListener("mouseup", stopDrag);
    }

    // Handle dragging
    function handleDrag(event: MouseEvent): void {
        if (dragging) {
            popupPosition = {
                x: event.clientX - dragOffset.x,
                y: event.clientY - dragOffset.y
            };
        }
    }

    // Stop dragging
    function stopDrag(): void {
        dragging = false;
        document.removeEventListener("mousemove", handleDrag);
        document.removeEventListener("mouseup", stopDrag);
    }
</script>


<div class="flex flex-col lg:flex-row w-full min-h-screen bg-gradient-to-b from-[#0f172a] to-[#111827] pt-20 px-4 lg:px-20 gap-10 overflow-x-hidden">
    <!-- KALENDARZ -->
    <div class="w-full lg:w-[800px]">
        <div class="text-center text-pink-400 mb-6">
            <h2 class="text-4xl font-extrabold bg-gradient-to-r from-purple-400 to-blue-400 text-transparent bg-clip-text">
                {months[currentMonth]} {currentYear}
            </h2>
        </div>

        <div class="flex justify-between mb-6">
            <button class="px-5 py-3 bg-gray-700 text-white rounded-md hover:bg-gray-600 transition" on:click={() => changeMonth(-1)}>
                Poprzedni
            </button>
            <button class="px-5 py-3 bg-gray-700 text-white rounded-md hover:bg-gray-600 transition" on:click={() => changeMonth(1)}>
                Następny
            </button>
        </div>

        <div class="grid grid-cols-7 gap-4 bg-[#1e293b] border border-pink-500 rounded-lg p-6 shadow-lg">
            {#each dates as { day, weekday, events, date }}
                <div
                    role="button"
                    class={`relative w-20 h-20 flex flex-col items-center justify-center text-sm font-semibold rounded-xl transition-all
                        ${
                            day === today.getDate() && currentMonth === today.getMonth() && currentYear === today.getFullYear()
                                ? 'bg-blue-600 text-white hover:scale-105'
                                : events.length > 0
                                    ? 'bg-pink-900/40 text-pink-200 hover:bg-pink-800/60 hover:scale-105'
                                    : isPastDay(day)
                                        ? 'bg-gray-800 text-gray-500'
                                        : 'bg-gray-700 text-gray-200 hover:bg-gray-600'
                        }`}
                    on:click={() => handleDayClick(events)}
                >
                    <div class="text-xs text-gray-400">{weekday}</div>
                    <div class="text-xl font-bold">{day}</div>
                    {#if events.length > 0}
                        <div class="absolute -top-1 -right-1 w-3 h-3 rounded-full bg-pink-500"></div>
                    {/if}
                </div>
            {/each}
        </div>
    </div>

    <!-- PRAWA SEKCJA -->
    <div class="w-full lg:w-[800px] mt-4 lg:mt-20 grid grid-cols-1 md:grid-cols-2 gap-6 self-start ml-auto">
        <!-- SZCZEGÓŁY -->
        <div class={`p-6 bg-[#1e293b] border rounded-lg shadow-lg transition-all duration-300 min-h-[300px] border-pink-500 ${hoveredEvents.length > 0 ? 'border-blue-400 shadow-blue-500' : ''}`}>
            <h3 class="text-2xl font-bold text-pink-400 mb-4">Szczegóły wydarzenia:</h3>
            {#if hoveredEvents.length > 0}
                <ul>
                    {#each hoveredEvents as event}
                        <li class="text-gray-300 mb-4">
                            <strong>{event.title}</strong><br />
                            {event.description}<br />
                            <span class="text-sm text-pink-300">
                                {event.location} - {event.venue}<br />
                                {event.start_date} - {event.end_date}
                            </span>
                        </li>
                    {/each}
                </ul>
                <button class="mt-4 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 transition-colors" on:click={() => handleWatchButtonClick(hoveredEvents[0])}>
                    Watch
                </button>
            {:else}
                <p class="text-gray-500 text-sm">Najedź na dzień z wydarzeniem</p>
            {/if}
        </div>

        <!-- MOJE -->
        <div class="p-6 bg-[#1e293b] border border-pink-500 rounded-lg shadow-lg min-h-[300px]">
            <h3 class="text-2xl font-bold text-pink-400 mb-4">Moje wydarzenia:</h3>
            <ul>
                {#each myEvents as event}
                    <li class="text-gray-300 mb-2">
                        <strong>{event.title}</strong> - {event.start_date}
                    </li>
                {/each}
            </ul>
        </div>
    </div>
</div>

{#if showPopup}
    <!-- Popup modal -->
    <div class="fixed top-0 left-0 w-full h-full bg-black bg-opacity-50 z-50 flex justify-center items-center" on:mousedown|stopPropagation>
        <div
            class="relative transition-all duration-500 ease-in-out"
            style="top: {popupPosition.y}px; left: {popupPosition.x}px; width: {isMinimized ? '20%' : '80%'}; height: {isMinimized ? '20%' : '80%'};"
            on:mousedown={startDrag}
        >
            <!-- Close and Minimize buttons -->
            <div class="absolute top-2 right-2 flex gap-2">
                <button class="px-4 py-2 bg-red-500 text-white rounded-lg hover:bg-red-600" on:click={closePopup}>X</button>
                <button class="px-4 py-2 bg-yellow-500 text-white rounded-lg hover:bg-yellow-600" on:click={minimizePopup}>_</button>
            </div>

            <!-- Popup content -->
            <div class="w-full h-full">
                <!-- YouTube player -->
                <iframe
                    width="100%"
                    height="100%"
                    src="{videoUrl}"
                    frameborder="0"
                    allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                    allowfullscreen
                ></iframe>
            </div>
        </div>
    </div>
{/if}
