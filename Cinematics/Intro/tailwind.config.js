/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{js,ts,jsx,tsx}'],
  theme: {
    extend: {
      fontFamily: {
        display: ['Space Grotesk', 'sans-serif'],
        sans: ['Inter', 'sans-serif'],
      },
      colors: {
        dark: '#0a0a0a',
        darker: '#050505',
        accent: {
          DEFAULT: '#ff4d00',
          light: '#ff6b2c',
        },
      },
    },
  },
  plugins: [],
};
