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
  </div>
</template>
<script setup>
import { ref, watch } from 'vue'

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
</script>

