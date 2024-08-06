<!-- 0_MachineFile.vue -->

<script setup>
import { ref, onMounted } from 'vue';
import ImageButton from '../../components/ImageButton.vue'
import GenerateButtonAssetNormal from '../../assets/Button_Blue_Long_Normal.svg'
import GenerateButtonAssetHover from  '../../assets/Button_Blue_Long_Over.svg'
import GenerateButtonAssetClick from  '../../assets/Button_Blue_Long_Click.svg'

import BackButton from '../../components/BackButton.vue'

const props = defineProps(['data']);
const licensingState = ref (props.data);

const emit = defineEmits(['buttonClicked']);

const generateMachineFile = () => {
    if (licensingState !== null) {
        // licensingState.value.generateMachineFile ();
        licensingState.value.generateMachineFile ((machineFile) => {
            console.log("Machine File generated", machineFile);
            emit ('buttonClicked', 'showOfflineInstructions');
        });
    } 
}

</script>

<template>
    <div>
        <div class="licensing-headline">
            <h1> Offline Activation </h1>
            <p1 style="color:#747474;"> Step 1 / 3 </p1>
        </div>
        <BackButton 
            @buttonClicked="$emit('buttonClicked', 'backToActivate')"
        />
        <ImageButton class="generate-button"
            :normalIcon="GenerateButtonAssetNormal"
            :hoverIcon="GenerateButtonAssetHover"
            :clickIcon="GenerateButtonAssetClick"
            buttonText="Generate Machine File"    
            @click="generateMachineFile"
        />
        <div class="machinefile-hint">
            <p1>
                This creates your personal Machine File
            </p1>
        </div>
    </div>
</template>

<style scoped>
.generate-button {
    position: fixed;
    /* Layout Properties */
    top: 225px;
    left: 195px;
    width: 302px;
    height: 68px;
    
}
.machinefile-hint {
    position: fixed;
    top: 311px;
    left: 200px;
    width: 287px;
    height: 19px;
    
    text-align: center;
    font: normal normal normal Roboto;
    letter-spacing: 0px;
    color: #747474;
    opacity: 1;
}
</style>