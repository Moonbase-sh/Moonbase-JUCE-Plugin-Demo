<script setup>
import { ref } from 'vue';

import BackButton from '../../components/BackButton.vue'
import DropFileNormalIcon from '../../assets/DropFile_Normal.svg'
import DropFileInterestedIcon from '../../assets/DropFile_Interested.svg'
import DropFileNotInterestedIcon from '../../assets/DropFile_NotInterested.svg'

const props = defineProps(['data']);
const licensingState = ref(props.data);

const emit = defineEmits(['buttonClicked', 'fileDropped']);
const interestingExtension = '.ylf'; // moonbase will need .mb here

const currentIcon = ref(DropFileNormalIcon);
const fileInputRef = ref(null);

const handleFileDrop = (event) => {
    event.preventDefault();
    const files = event.dataTransfer.files;
    if (files.length && files[0].name.endsWith(interestingExtension)) {
        // emit('fileDropped', files);
        //gotta handle file drop here
        currentIcon.value = DropFileNormalIcon;
    } else {
        event.dataTransfer.effectAllowed = 'none';
        event.dataTransfer.dropEffect = 'none';
    }
};

const handleDragOver = (event) => {
    event.preventDefault();
    const file = event.dataTransfer.items[0];
    if (file.kind === 'file' && file.type && file.getAsFile().name.endsWith(interestingExtension)) {
        currentIcon.value = DropFileInterestedIcon;
    } else {
        currentIcon.value = DropFileNotInterestedIcon;
    }
};

const handleClick = () => {
    fileInputRef.value.click();
};

const preventDefault = (event) => event.preventDefault();
</script>

<template>
    <div>
        <div class="licensing-headline">
            <h1> Offline Activation </h1>
            <p1 style="color:#747474;"> Final step </p1>
        </div>
        <BackButton 
            @buttonClicked="$emit('buttonClicked', 'backToActivate')"
        />
        <div class="license-drop-hint">
            <h2> Drop your license file below </h2>
        </div>
        <div class="file-drop-area"
            @drop="handleFileDrop"
            @dragover="handleDragOver"
            @dragenter="preventDefault"
            @dragleave="() => currentIcon.value = DropFileNormalIcon"
            @click="handleClick">
            <img :src="currentIcon" alt="Drop file area">
            <input type="file" ref="fileInputRef" @change="handleFileDrop" accept=".ylf" style="display: none;">
        </div>
    </div>
</template>

<style scoped>
.license-drop-hint {
    position: fixed;
    top: 169px;
    left: 66px;
    width: 560px;
    height: 25px;
    text-align: center;
    font: normal normal medium 22px/32px Roboto;
    letter-spacing: 0px;
    color: #D0D0D0;
    opacity: 1;
}

.file-drop-area {
    position: fixed;
    top: 236px;
    left: 117px;
    width: 457px;
    height: 176px;
    cursor: pointer;
}

input[type="file"] {
    width: 100%;
    height: 100%;
    position: absolute;
}
</style>
