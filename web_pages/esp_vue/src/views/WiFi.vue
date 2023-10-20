<template>
  <main>
    <div class="container-fluid">
      <div class="row mt-5 justify-content-center text-center">
        <div class="col-sm-8">
          <div class="card">
            <div class="card-header bg-primary">
              <h6 class="text-center">WiFi NetWork Scan</h6>
            </div>
            <div class="card-body">
              <table class="table">
                <thead>
                  <tr>
                    <th scope="col">ID</th>
                    <th scope="col">Name</th>
                    <th scope="col">Channel</th>
                    <th scope="col">Auth Mode</th>
                    <th scope="col">RSSI</th>
                  </tr>
                </thead>
                <tbody>
                  <tr v-for="(wifi, index) in found_wifis" :key="wifi.SSID">
                    <th scope="row">{{ index }}</th>
                    <td>{{ wifi.SSID }}</td>
                    <td>{{ wifi.CH }}</td>
                    <td>{{ wifi.authmode }}</td>
                    <td>{{ wifi.RSSI }}</td>
                  </tr>
                </tbody>
              </table>
            </div>
            <div class="card-footer">
              <div class="row justify-content-center">
                <div class="col-sm-12">
                  <p>
                    <strong>{{ message }}</strong>
                  </p>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </main>
</template>

<script setup>
import { onMounted, ref } from "vue";

const found_wifis = ref([]);
const message = ref("Loading...");

onMounted(() => {
  console.log("Component mounted");
  fetch("/api/wifi_scan")
    .then((response) => response.json())
    .then((wifis) => {
      console.log(wifis);
      found_wifis.value = wifis;
      console.log(found_wifis);
      message.value = wifis.length + " WiFi Found on the Network";
    });
});
</script>
