<!-- Welcome.vue -->
<script setup>
import MoonbaseLogo from '../assets/MoonbaseLogo.svg'

import ImageButton from '../components/ImageButton.vue'
import ButtonAssetNormal from '../assets/Button_Blue_Long_Normal.svg'
import ButtonAssetHover from '../assets/Button_Blue_Long_Over.svg'
import ButtonAssetClick from '../assets/Button_Blue_Long_Click.svg'


const emit = defineEmits(['buttonClicked']);

const startButtonClicked = () => {
    emit('buttonClicked', 'startActivation');
}
</script>

<template>
    <div>
        <div class="welcome-text">
            <h2>Weightless<br>License Management</h2>        
        </div>
        <img :src="MoonbaseLogo" class="logo"/>
        <ImageButton class="start-activation"
            :normalIcon="ButtonAssetNormal"
            :hoverIcon="ButtonAssetHover"
            :clickIcon="ButtonAssetClick"
            buttonText="Start Activation"      
            :onClick="startButtonClicked"  
        />

    </div>
</template>

<style scoped>
.logo {
    position: fixed;
    top: 62px;
    left: 283px;
    width: 124px;
    height: 48px;
}


.start-activation {
    position: fixed;
    top: 375px;
    left: 194px;
    width: 303px;
    height: 69px;
}

.welcome-text {
    position: fixed;
    top: 232px;
    left: 211px;
    width: 270px;
    height: 54px;
    /* UI Properties */
    text-align: center;
    font: normal normal medium 23px/27px Roboto;
    letter-spacing: 0px;
    color: #D0D0D0;
    opacity: 1;
}


</style>

<style>
    .licensing-headline {
        position: fixed;
        top: 21px;
        left: 111px;
        width: 470px;
        height: 35px;
        /* UI Properties */
        text-align: center;
        font: normal normal bold Roboto;
        letter-spacing: 0px;
        color: #D0D0D0;
        opacity: 1;
    }
</style>