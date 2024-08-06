<!-- YumSpinner.vue-->

<script setup>

import Logo from './assets/Logo.svg'
import Ring1 from './assets/Ring1.svg'
import Ring2 from './assets/Ring2.svg'
import Ring3 from './assets/Ring3.svg'

</script>


<template>
    <div class="spinner"> 
        <img :src="Logo" class="spinner-logo"/>
        <img :src="Ring1" class="spinner-ring1"/>
        <img :src="Ring2" class="spinner-ring2"/>
        <img :src="Ring3" class="spinner-ring3"/>
    </div>
</template>


<style scoped>
.spinner {
    position: absolute;
}

.spinner-logo, .spinner-ring1, .spinner-ring2, .spinner-ring3 {
    position: absolute;
    top: 0;
    left: 0;
}

.spinner-logo {
    scale: 0.3;
}

.spinner-ring1 {
    animation: spin 4.4s linear infinite;
}

.spinner-ring2  {
    animation: spinCounter 3s linear infinite;
}

.spinner-ring3 {
    animation: spin 3s linear infinite;
}


@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}

@keyframes spinCounter {
    0% { transform: rotate(360deg); }
    100% { transform: rotate(0deg); }
}

</style>
    