
<script setup>
import { ref } from 'vue';

const props = defineProps({
  normalIcon: String,
  hoverIcon: String,
  clickIcon: String,
  onClick: Function,
  altText: String,
  buttonText: String,
});

const currentIcon = ref(props.normalIcon);

const handleMouseOver = (isOver) => {
  currentIcon.value = isOver ? props.hoverIcon : props.normalIcon;
};

const handleMouseDown = (isDown) => {
  currentIcon.value = isDown ? props.clickIcon : props.normalIcon;
};
</script>



<template>
    <button 
        @mouseenter="handleMouseOver(true)" 
        @mouseleave="handleMouseOver(false)"
        @mousedown="handleMouseDown(true)"
        @mouseup="handleMouseDown(false)"
        @click.stop="onClick"
        class="button-container"
    >
        <img :src="currentIcon" :alt="altText">
        <span class="button-text">{{ buttonText }}</span>
    </button>
</template>


<style scoped>

.button-container {
  display: flex;
  position: relative;
  border: none;
  height: 100%;
  align-items: center;
  cursor: pointer;
  background-color: transparent;
}

.button-container img {
  height: 100%;
  width: 100%;
}

.button-container .button-text {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    font-size: 23px;
    font-weight: bold;
    text-wrap: nowrap;
    color: white;
    z-index: 1;
}

</style>
