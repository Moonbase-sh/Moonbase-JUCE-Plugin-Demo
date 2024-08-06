<!-- 1_Instructions.vue -->

<script setup>
import { ref, onMounted } from 'vue';
import ImageButton from '../../components/ImageButton.vue'
import NextButtonAssetNormal from '../../assets/Button_Blue_Short_Normal.svg'
import NextButtonAssetHover from  '../../assets/Button_Blue_Short_Over.svg'
import NextButtonAssetClick from  '../../assets/Button_Blue_Short_Click.svg'

import BackButton from '../../components/BackButton.vue'

const props = defineProps(['data']);
const licensingState = ref (props.data);

const emit = defineEmits(['buttonClicked']);

const openOfflineActivationPage = () => {
    licensingState.value.openInExternalBrowserWindow('https://yum-audio.com/activate');
};

</script>

<template>
    <div>
        <div class="licensing-headline">
            <h1> Offline Activation </h1>
            <p1 style="color:#747474;"> Step 2 / 3 </p1>
        </div>
        <BackButton 
            @buttonClicked="$emit('buttonClicked', 'backToActivate')"
        />
        <div class="licensing-offlince-instructions">
            <p1>
                <br/>
                Take your machine file to a computer, that's connected to the internet and visit
                <br/><br/><br/>
               <button
                    @click="openOfflineActivationPage"
                    style="background-color: transparent; border: none; color: #D0D0D0; text-decoration: underline;"
                >
                    <u>yum-audio.com/activate</u>
               </button>
               <br/><br/><br/>
               Follow the instructions on the website and download your license file. Once you have it, click on 'Next'.
            </p1>
        </div>
        <ImageButton class="next-button"
            :normalIcon="NextButtonAssetNormal"
            :hoverIcon="NextButtonAssetHover"
            :clickIcon="NextButtonAssetClick"
            buttonText="Next"    
            @click="$emit('buttonClicked', 'showOfflineLicenseDrop')"
        />
    </div>

</template>

<style scoped lang="scss">
$width: 60%;
.licensing-offlince-instructions {
    position: fixed;
    /* Layout Properties */

    text-align: center;
    top: 133px;
    left: calc((100% - #{$width}) / 2);
    width: #{$width};
    /* UI Properties */

    font: normal normal normal Roboto;
    letter-spacing: 0px;
    color: #D0D0D0;
    opacity: 1;
}

.next-button {
    position: fixed;
    /* Layout Properties */
    top: 427px;
    left: 483px;
    width: 184px;
    height: 68px;
}

</style>