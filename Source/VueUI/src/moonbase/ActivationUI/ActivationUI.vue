<script setup>
import { ref, computed, watch } from 'vue'
import useLicensing from '../composables/useLicensing.js'
import useAbsoluteScalingComponent from '../composables/useAbsoluteScalingComponent.js'

import LicensingPages from './LicensingPages.vue'
import ActivatedPage from './pages/3_Activated.vue'

import ImageButton from './components/ImageButton.vue'
import CloseButtonAssetNormal from './assets/Close_Normal.svg'
import CloseButtonAssetHover from './assets/Close_Over.svg'
import CloseButtonAssetClick from './assets/Close_Click.svg'

import BGAsset from './assets/BG.svg';

const state = ref (useLicensing ());


const shouldBeVisible = computed (() => {
    return state?.value.shouldBeVisible ();
});

const closeButtonVisible = computed (() => {
    return ! state?.value.mustBeVisible ();
});

const isFullyActivated = computed (() => {
    return state?.value.isFullyActivated ();
});

function handleCloseRequest () {
    console.log('handleCloseRequest');
    state?.value?.requestToggleVisibility();
}

function requestToggleVisibility () {
    state?.value?.requestToggleVisibility();
}

const pageContainer = ref(null);
const activatedPage = ref(null);

const scalingComp = useAbsoluteScalingComponent (pageContainer, 692, 518, 1, 0.04);

defineExpose({ state, requestToggleVisibility });

</script>

<template> 
    <div v-if="shouldBeVisible" class="licensing" @click.stop="handleCloseRequest" >
        <div class="pageContainer" ref="pageContainer">

            <img :src="BGAsset" class="background-image" />
            <Transition name="fade" >
                <div v-if="isFullyActivated" @click.stop>
                    <ActivatedPage class="pageContainer" @click.stop 
                        :ref="activatedPage"
                        :data="state"
                    />
                </div>
                <div v-else>
                    <LicensingPages @click.stop 
                        :data="state"
                    />
                </div>
            </Transition>
            <ImageButton v-if="closeButtonVisible" class="closeButton"
                :normalIcon="CloseButtonAssetNormal"
                :hoverIcon="CloseButtonAssetHover"
                :clickIcon="CloseButtonAssetClick"
                altText="X"
                @click.stop="handleCloseRequest"
            />
        </div>
    
    </div>

</template>

<style scoped>

.licensing {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    z-index: 9999;
    padding: 15px;
    box-sizing: border-box;
}

.pageContainer {
    position: absolute;
    width: 692px;
    height: 518px;
}

.background-image {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
}


.closeButton {
    position: fixed;
    top: calc(307px - 281px);
    left: calc(1000px - 374px);
    width: 36px;
    height: 36px;
    z-index: 200;
}


</style>