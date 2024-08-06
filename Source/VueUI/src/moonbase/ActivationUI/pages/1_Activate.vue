<script setup>
import { ref, onMounted, nextTick } from 'vue';
import ImageButton from '../components/ImageButton.vue'
import LetsGoButtonAssetNormal from '../assets/Button_Blue_Short_Normal.svg'
import LetsGoButtonAssetHover from  '../assets/Button_Blue_Short_Over.svg'
import LetsGoButtonAssetClick from  '../assets/Button_Blue_Short_Click.svg'

import BackButton from '../components/BackButton.vue'

import eventBus from './eventBus';

const props = defineProps(['data']);
const licensingState = ref (props.data);


const emit = defineEmits(['buttonClicked']);

const letsGoButtonClicked = () => {
    if (licensingState !== null) {
        licensingState.value.requestAutoActivation ((success) => {
            console.log ("Received finish callback", success);
            if (! success)
            {
                console.log ("Failed to finish auto activation"); 
                eventBus.emit('buttonClicked', 'backToActivate');
            }
        
        });
        emit('buttonClicked', 'beginAutoActivation');
    } 
}

const offlineButtonClicked = () => {
    if (licensingState !== null) {
        emit('buttonClicked', 'beginOfflineActivation');
    } 
}

</script>

<template>
    <div>
        <div class="licensing-headline">
            <h1> Activation </h1>
        </div>
        <BackButton 
            @buttonClicked="$emit('buttonClicked', 'backToWelcome')"
        />
        <ImageButton class="lets-go-button"
            :normalIcon="LetsGoButtonAssetNormal"
            :hoverIcon="LetsGoButtonAssetHover"
            :clickIcon="LetsGoButtonAssetClick"
            buttonText="Let's go!"    
            :onClick="letsGoButtonClicked"   
        />
        <div>
            <p1 class="activate-line-1"> Opens your browser for </p1>
            <h4 class="activate-line-2"> Trial & Activation </h4>
        </div>

        <button class="offline-activation-btn" 
            @click="offlineButtonClicked"
        >    
            <h4>Offline Activation</h4>
        </button>

    </div>
</template>

<style scoped>

.lets-go-button {
    position: fixed;
    top: 225px;
    left: 254px;
    width: 181px;
    height: 65px;
}

.activate-line-1 {
    position: fixed;
    /* Layout Properties */
    top: 305px;
    left: 252px;
    width: 188px;
    height: 21px;
    /* UI Properties */
    text-align: center;
    font: normal normal normal Roboto;
    letter-spacing: 0.07px;
    color: #D0D0D0;
    opacity: 1;
}

.activate-line-2 {
    position: fixed;
    /* Layout Properties */
    top: 330px;
    left: 269px;
    width: 154px;
    height: 24px;
    /* UI Properties */
    text-align: center;
    font: normal normal medium 20px/25px Roboto;
    letter-spacing: 0.08px;
    color: #D0D0D0;
    opacity: 1;
}

.offline-activation-btn {
    position: fixed;
    /* Layout Properties */
    top: 431px;
    left: 268px;
    width: 156px;
    height: 24px;
    /* UI Properties */
    text-align: center;
    font: normal normal medium 20px/24px Roboto;
    letter-spacing: 0.12px;
    color: #747474;
    opacity: 1;
    background-color: transparent;
}
.offline-activation-btn:hover {
    color: #D0D0D0;
}
</style>