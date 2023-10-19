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

    <div class="form-check form-switch">
  <input class="form-check-input"   type="checkbox" v-model="led_state" role="switch" id="flexSwitchCheckDefault">
  <label class="form-check-label" for="flexSwitchCheckDefault">LED State {{ led_state }}</label>

</div>
  </div>
</template>
<script setup>
import { onMounted, ref, watch } from 'vue'
import axios from 'axios';

const number1 = ref(0)
const number2 = ref(0)
const result = ref(0)
const led_state = ref(false)
watch(number1, async (newNumber, oldNumber) => {
    result.value = newNumber + number2.value;
})

watch(number2, async (newNumber, oldNumber) => {
  result.value= newNumber + number1.value;
  console.log(result.value)
})


onMounted(()=>{
   axios.get("/api/led_command").then(response=>{
    console.log('Getting the LED state from the server',response.data)
    led_state.value = response.data.state ;
   })
})

const set_led_state = async function(state){
  console.log(state)
  let data = {
    name: "led1",
    state:state
  }
  

  axios.post("/api/led_command", data).then((response)=>{
    console.log(response.data)
    led_state.value = response.data.state ;
  })
/*const response =  await fetch('/api/led_command');
  const data_jon  = await response.json();
  console.log(data_jon);
*/
  
}
</script>

