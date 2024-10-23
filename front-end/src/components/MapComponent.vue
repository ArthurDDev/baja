<template>
  <GMapMap
    :center="{ lat: -25.450677, lng: -49.231746 }"
    :zoom="17"
    :options="{
      zoomControl: true,
      mapTypeControl: true,
      scaleControl: true,
      streetViewControl: false,
      rotateControl: true,
      fullscreenControl: true,
    }"
    map-type-id="satellite"
    style="width: 100vw; height: 900px"
  >
    <GMapMarker
      :key="marker.id"
      v-for="marker in markers"
      :position="{ lat: marker.lat, lng: marker.lng }"
      :clickable="true"
      :draggable="true"
    />
  </GMapMap>
</template>

<script>
/*TODO
Eu nao sei exatamente como a API do google funciona
pode ser que seja possivel colocar as linhas, pode ser que nao.
De qualquer forma a documentação é muito ruim para saber como fazer isso
e o que já existe é suficiente
*/
import axios from 'axios';

export default {
  name: 'App',
  data() {
    return {
      center: { lat: 10, lng: 10 },
      zoom: 7,
      mapOptions: {
        styles: [
          {
            featureType: 'all',
            elementType: 'labels',
            stylers: [{ visibility: 'off' }],
          },
        ],
      },
      markers: [] 
    };
  },
  mounted() {
    this.fetchMarkers(); 
  },
  methods: {
    async fetchMarkers() {
      try {
        const response = await axios.get('http://localhost:8000/api/marker');
        this.markers = response.data.marker;
      } catch (error) {
        console.error('Error fetching markers:', error);
      }
    }
  }
}
</script>
