<script setup>
import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div class="container-fluid">
     <div class="row">
      <nav class="navbar navbar-expand-lg navbar navbar-dark bg-dark">
        <a class="navbar-brand" href="/"> <strong>VUE ESP32</strong></a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarText" aria-bs-controls="navbarText" aria-bs-expanded="false" aria-bs-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarText">
          <ul class="navbar-nav mr-auto">
            <li class="nav-item active m-1">
              <RouterLink  class="btn btn-primary mx-2" to="/">Home</RouterLink>
            </li>
            <li class="nav-item m-1">
              <RouterLink class="btn btn-warning mx-2" to="/leds">LED</RouterLink>
            </li>
            <li class="nav-item m-1">
              <RouterLink class="btn btn-secondary mx-2" :to="{name:'WiFi'}">WiFi</RouterLink>
            </li>
          </ul>
          
        </div>
      </nav>
    </div>

    <div class="row">
      <RouterView />
    </div>
    <div class="col-sm-12 mt-5">
      <div class="card ">
      <div class="card-headeer">
          <p>This is the footer</p>
      </div>
    </div>
    </div>
    

  </div>


 
</template>
