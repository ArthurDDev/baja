<template>
    <GMapMap
        :center="{lat: -25.450677, lng: -49.231746}"
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
      :key="index"
      v-for="(m, index) in markers"
      :position="m.position"
      :clickable="true"
      :draggable="true"
    />
    </GMapMap>
  </template>
  
  <script >
  export default {
    name: 'App',
    data() {
    return {
      center: { lat: 10, lng: 10 },
      zoom: 7,
      mapOptions: {
        styles: [
          {
            featureType: 'all', // Target all feature types
            elementType: 'labels', // Specifically target labels
            stylers: [{ visibility: 'off' }], // Turn off visibility
          },
        ],
      },
      markers: [
        {
          position: {
            lat: -25.450677, lng: -49.231746
          },
        },
        {
          position: {
            lat: -25.550500, lng: -49.231746
          },
        }
      ]
    };
  },
  }
  </script>
  