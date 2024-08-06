<script setup>

import ImageButton from './ImageButton.vue'

import BackButtonAssetNormal from '../assets/Back_Normal.svg'
import BackButtonAssetHover from '../assets/Back_Over.svg'
import BackButtonAssetClick from '../assets/Back_Click.svg'

const props = defineProps ({
    destination: {
        type: String,
        default: 'backToWelcome'
    }
});

const emit = defineEmits(['buttonClicked']);

const backButtonClicked = () => {
    emit('buttonClicked');
}
</script>

<template>
    <div>
        <ImageButton class="back-button"
            :normalIcon="BackButtonAssetNormal"
            :hoverIcon="BackButtonAssetHover"
            :clickIcon="BackButtonAssetClick"
            altText="X"
            :onClick="backButtonClicked"
        />
    </div>
</template>

<style scoped>

.back-button {
    position: fixed;
    /* Layout Properties */
    top: 26px;
    left: 28px;
    width: 36px;
    height: 36px;
    /* UI Properties */
    opacity: 1;
}

</style>