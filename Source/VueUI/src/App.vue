<script setup>
import { ref } from 'vue';
import ActivationUI from './moonbase/ActivationUI/ActivationUI.vue'

const activationUi = ref(null);

function openActivationWindow() {
  if (activationUi.value) {
      activationUi.value.requestToggleVisibility();
  }
}

</script>

<template>
  <div>
    <ActivationUI ref="activationUi" class="licensing-overlay" />
    <button @click="openActivationWindow" class="activation-button">Open Activation Window</button>
  </div>
 
</template>

<style scoped>
html, body, #app {
    overflow-x: hidden !important;
    overflow-y: hidden !important;
}

.licensing-overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: 9999;
}

.activation-button {
  position: relative;
  z-index: 0;
  border-radius: 12px;
  padding: 10px 20px;
  font-size: 16px;
  cursor: pointer;
  margin: 20px;
}

</style>
