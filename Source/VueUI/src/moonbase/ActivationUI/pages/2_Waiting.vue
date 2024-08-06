<!-- Waiting.vue -->
<script setup>
import { ref } from 'vue'
import BackButton from '../components/BackButton.vue'
import Spinner from '../components/Spinner/Spinner.vue'

const props = defineProps(['data']);
const licensingState = ref (props?.data);

const emit = defineEmits(['buttonClicked']);

const backButtonClicked = () => {
    if (licensingState !== null) {
        licensingState.value.interruptAutoActivation ();
        emit('buttonClicked', 'backToActivate');
    }
}

</script>

<template>
    <div>
        <BackButton
            @buttonClicked="backButtonClicked"
        />
        <Spinner class="yum-spinner" />
        <div class="continue-in-browser-txt">
            <p1>Continue in browser</p1>
        </div>
    </div>
</template>

<style scoped lang="scss" >

$spinnerSize: 150px;

.yum-spinner {
    position: fixed;
    top: calc(50% - #{$spinnerSize} / 2);
    left: calc(50% - #{$spinnerSize} / 2);
    width: #{$spinnerSize};
    height: #{$spinnerSize};
}

.start-activation {
    position:fixed;
    top: 375px;
    left: 201px;
    width: 303px;
    height: 69px;
}

.continue-in-browser-txt {
    position: fixed;
    /* Layout Properties */
    top: 350px;
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
</style>