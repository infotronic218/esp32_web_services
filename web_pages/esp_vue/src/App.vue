<script setup>
import { RouterLink, RouterView } from "vue-router";
</script>

<template>
  <div id="content-wrap" class="container-fluid">
    <div class="row">
      <nav class="navbar navbar-expand-lg navbar navbar-dark bg-dark">
        <a class="navbar-brand" href="/"> <strong>VUE ESP32</strong></a>
        <button
          class="navbar-toggler"
          type="button"
          data-bs-toggle="collapse"
          data-bs-target="#navbarText"
          aria-bs-controls="navbarText"
          aria-bs-expanded="false"
          aria-bs-label="Toggle navigation"
        >
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav mr-auto">
            <li class="nav-item active m-1">
              <RouterLink class="btn btn-primary" to="/">Home</RouterLink>
            </li>
            <li class="nav-item m-1">
              <RouterLink class="btn btn-warning" to="/leds">LED</RouterLink>
            </li>
            <li class="nav-item m-1">
              <RouterLink class="btn btn-secondary" :to="{ name: 'WiFi' }">
                WiFi
              </RouterLink>
            </li>
          </ul>
        </div>
      </nav>
    </div>

    <div class="row">
      <RouterView />
    </div>
  </div>

  <div id="footer" class="container-fluid">
    <div class="row bg-dark">
      <div class="col-sm-12">
        <div class="card bg-dark">
          <div class="card-body">
            <p class="text-center text-white">VueJS On ESP32 @ 2023</p>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style>
.page-container,
#app {
  position: relative;
  min-height: 100vh;
}

#content-wrap {
  padding-bottom: 2.5rem; /* Footer height */
}

#footer {
  position: absolute;
  bottom: 0;
  width: 100%;
  height: 2.5rem; /* Footer height */
}
</style>
