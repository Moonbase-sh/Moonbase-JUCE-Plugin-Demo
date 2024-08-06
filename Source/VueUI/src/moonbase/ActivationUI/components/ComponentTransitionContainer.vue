<script setup>
import { ref, watch } from 'vue';
import '../assets/main.css'

const props = defineProps({
    data: Object,
    components: Array
});
const data = ref(props?.data);

const emit = defineEmits(['buttonClicked']);
const currentComponent = ref(props.components[0]);
const transitionName = ref('fade');

function showPage(x, direction) {
    let index = props.components.indexOf(x);
    if (index === -1) return;

    //we should transition here... 
    transitionName.value = direction;
    console.log("showPage", x, transitionName.value);
    currentComponent.value = x;
}

function showImmediate(x) {
    showPage(x, 'snap');
}

defineExpose({ showPage, showImmediate });

</script>

<template>
    <div class="transition-container">
        <Transition :name="transitionName">
            <component 
                :is="currentComponent" 
                :data="data"
                @buttonClicked="$emit('buttonClicked', $event)" 
                :key="componentKey">
            </component>
        </Transition>
    </div>
</template>

<style scoped>
.transition-container {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    z-index: 100;
    overflow: hidden;
}

</style>