import { createApp } from 'vue';
import App from './App.vue';

import  VueGoogleMaps from '@fawmi/vue-google-maps'

const app = createApp(App);
app.use(VueGoogleMaps, {
    load: {
        key: 'AIzaSyBRhpNOTFPfZrG3-r-Vu6XovOIskQoUCaU',
    },
}).mount('#app')
