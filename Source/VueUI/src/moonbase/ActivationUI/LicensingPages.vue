<!-- LicensingPages.vue -->
<script setup>
import { ref, onMounted, onBeforeUnmount } from 'vue';

import ComponentTransitionContainer from './components/ComponentTransitionContainer.vue';

import WelcomePage from './pages/0_Welcome.vue';
import ActivatePage from './pages/1_Activate.vue';
import WaitingPage from './pages/2_Waiting.vue';

import OfflinePage1 from './pages/offline/0_MachineFile.vue'
import OfflinePage2 from './pages/offline/1_Instructions.vue'
import OfflinePage3 from './pages/offline/2_LicenseDrop.vue'

import eventBus from './pages/eventBus';

const props = defineProps(['data']);
const licensingState = ref(props?.data);

const transContainer = ref(null);

const handleButtonClicked = (event) => {
    console.log("Button clicked", event);
    try {
        if (event === 'startActivation') 
            transContainer.value.showPage (ActivatePage, 'slide-left')
        else if (event === 'beginAutoActivation')
            transContainer.value.showPage (WaitingPage, 'slide-left')
        else if (event === 'beginOfflineActivation')
            transContainer.value.showPage (OfflinePage1, 'slide-left')
        else if (event === 'showOfflineInstructions')
            transContainer.value.showPage (OfflinePage2, 'slide-left')
        else if (event == 'showOfflineLicenseDrop')
            transContainer.value.showPage (OfflinePage3, 'slide-left')
        else if (event == 'backToActivate')
            transContainer.value.showPage (ActivatePage, 'slide-right')
        else if (event === 'backToWelcome')
            transContainer.value.showPage (WelcomePage, 'slide-right')
    } catch (error) {
        console.error("Error in handleButtonClicked", error);
    }
}

onMounted (() => {
    eventBus.on('buttonClicked', handleButtonClicked);
});
onBeforeUnmount (() => {
    eventBus.off('buttonClicked');
});

</script>

<template>
    <div>
        
        <ComponentTransitionContainer
            ref="transContainer"
            class="trans-container"
            :data="licensingState"
            :components="[
                WelcomePage, 
                ActivatePage, 
                WaitingPage, 
                OfflinePage1,
                OfflinePage2,
                OfflinePage3
            ]"
            @buttonClicked="handleButtonClicked"
        />
    </div>
</template>



<style scoped>



.trans-container {
    position: absolute;
    max-width: 692px;
    max-height: 550px;
}



</style>

