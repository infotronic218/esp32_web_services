<template>
  <div class="container">
    <h1 class="text-center text-uppercase">LED page</h1>
    <div class="row">
         <div class="col-sm-4 m-1">
            <input v-model="number1" type="number"  class="form-control">
         </div>
         <div class="col-sm-4 m-1">
            <input v-model="number2" type="number"  class="form-control">
         </div>
         <div class="col-sm-4">
            <label>Result: {{ result }}</label>
         </div>
    </div>
    <div class="row">
        <button v-on:click="set_led_state(true)" class="col-sm-2 m-1 btn btn-success">ON</button>
        <button v-on:click="set_led_state(false)"  class="col-sm-2 m-1 btn btn-danger">OFF</button>
    </div>
  </div>
</template>
<script setup>
import { ref, watch } from 'vue'
import axios from 'axios';

const number1 = ref(0)
const number2 = ref(0)
const result = ref(0)
watch(number1, async (newNumber, oldNumber) => {
    result.value = newNumber + number2.value;
})

watch(number2, async (newNumber, oldNumber) => {
  result.value= newNumber + number1.value;
  console.log(result.value)
})

const set_led_state = async function(state){
  console.log(state)
  let data = {
    name: "led1",
    state:state
  }
  
  /*
  axios.get("/api/leds_json", {}).then((response)=>{
    console.log(response)
  })*/
  const response =  await fetch('/api/leds_json');
  const data_jon  = await response.json();
  console.log(data_jon);

  
}
</script>

