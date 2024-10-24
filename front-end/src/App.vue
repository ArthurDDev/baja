<template>
  <div class="map-container">
    <h1>GPS</h1>
    <div class="map-div">
      <MapComponent class="map"/>
    </div>
  </div>
  <div class = "spacer"></div>
  <div class = table-container>
    <h1>Telemetria</h1>
    <table border="1" class = "table">
    <thead>
      <tr>
        <th>Tempo</th>
        <th>Sensor 1</th>
        <th>Sensor 2</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>1</td>
        <td>Dado 1</td>
        <td>Dado a</td>
      </tr>
      <tr>
        <td>2</td>
        <td>Dado 2</td>
        <td>Dado b</td>
      </tr>
      <tr>
        <td>3</td>
        <td>Dado 3</td>
        <td>Dado c</td>
      </tr>
    </tbody>
    </table>
  </div>
</template>

<style>

  .table-container {
    display: flex;
    justify-content: center;
    flex-direction: column;
    align-items: center;
  }

  .table {
    width: 50%;
    text-align: center;
  }

  .spacer {
    height: 10vh;
  }

  .map-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
  }

  .map-div {
    display: flex;
  }

  .map {
    display: flex;
    width: 100%;
    height: 80vh;
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
