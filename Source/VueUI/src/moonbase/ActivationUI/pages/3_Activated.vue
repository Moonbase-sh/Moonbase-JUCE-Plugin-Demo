<!-- 3_Activated.vue -->

<script setup>

import { ref, computed } from 'vue';
import MoonbaseLogo from '../assets/MoonbaseLogo.svg'

import ImageButton from '../components/ImageButton.vue'
import DisableButtonAssetNormal from '../assets/Button_Red_Long_Normal.svg'
import DisableButtonAssetHover from  '../assets/Button_Red_Long_Over.svg'
import DisableButtonAssetClick from  '../assets/Button_Red_Long_Click.svg'

const props = defineProps(['data']);
const licensingState = ref (props.data);

const emit = defineEmits(['buttonClicked']);

const deactivateButtonClicked = () => {
    if (licensingState !== null) {
        licensingState.value.deactivateLicense ();
        emit('buttonClicked', 'deactivateLicense');
    } 
}

const productVerion = computed (() => {
    return licensingState?.value?.getVersion ();
}); 

const getCurrentYear = () => {
    return new Date().getFullYear();
}

const activationType = computed (() => {
    return licensingState?.value?.getActivationType ();
});

const userIdentification = computed (() => {
    return licensingState?.value?.getUserIdentification ();
});

const licenseId = computed (() => {
    return licensingState?.value?.getLicenseId ();
});

</script>

<template>
    <div>
        <img :src="MoonbaseLogo" class="logo" />
        
        <ImageButton class="deactivate-button"
            :normalIcon="DisableButtonAssetNormal"
            :hoverIcon="DisableButtonAssetHover"
            :clickIcon="DisableButtonAssetClick"
            buttonText="Deactivate"      
            :onClick="deactivateButtonClicked"  
        />
        <div class="license-info allowSelect">
            © {{ getCurrentYear () }} Yum Audio. All rights reserved.  <br/>
            Version: {{ productVerion }} <br/>
            Activation Type: {{ activationType }} <br/>
            Registered to: {{ userIdentification }} <br/>
            License ID: <br/> {{ licenseId }}
        </div>
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

.deactivate-button {
    position: fixed;
    top: 375px;
    left: 194px;
    width: 303px;
    height: 69px;
}

.license-info {
    position: fixed;
    /* Layout Properties */
    top: 222px;
    left: 29px;
    width: 634px;
    height: 126px;
    /* UI Properties */
    text-align: center;
    font: normal normal normal  Roboto;
    letter-spacing: 0px;
    color: #D0D0D0;
    opacity: 1;
    line-height: 21px;
}

</style>