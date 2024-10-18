<template>
  <div>
    <h1>Localizacao</h1>
    <div class="map-container">
      <MapComponent class="map"/>
    </div>
  </div>
</template>

<style>

  .map-container {
    width: 400px;
    height: 400px;
  }

  .map {
    width: 400px,;
    height: 300px;
  }

</style>

<script>
import MapComponent from './components/MapComponent.vue';

export default {
  components: {
    MapComponent,
  },
};
</script>
