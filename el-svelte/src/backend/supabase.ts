import { createClient } from '@supabase/supabase-js'

const supabaseUrl = 'https://jsssjspfxyvjanuvangk.supabase.co'
const supabaseKey = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Impzc3Nqc3BmeHl2amFudXZhbmdrIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDI2NjI5NDEsImV4cCI6MjA1ODIzODk0MX0.de2jxTulWJIKqSn80NkBJyGPlUmRYLI83Fosy60PRg0'

export const supabase = createClient(supabaseUrl,supabaseKey)
console.log('✅ Supabase client created successfully:', supabase);
