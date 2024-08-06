import { watchEffect, onMounted, onBeforeUnmount } from 'vue'

export default function useAbsoluteScalingComponent (divRef, width, height, maxScale = 1, extraReductionOnShrink = 0) {

    const divToControl = divRef;
    const divWidth = width;
    const divHeight = height;
    const divMaxScale = maxScale;
    const divExtraShrinkReduction = extraReductionOnShrink;

    const resizeDiv = () => {
        if (divToControl.value) {
            const parentWidth = divToControl.value.parentNode.clientWidth;
            const parentHeight = divToControl.value.parentNode.clientHeight;
        
            const scaleWidth = parentWidth / divWidth; 
            const scaleHeight = parentHeight / divHeight; 
        
            let scale = Math.min (divMaxScale, Math.min(scaleWidth, scaleHeight));
            
            if (scale < 1) {
                scale -= divExtraShrinkReduction; //for some extra padding from the sides
            }
            divToControl.value.style.transform = `scale(${scale})`;
        }
    };

    watchEffect(() => {
        if (divToControl.value) {
            resizeDiv();
        }
    }); 
    
    onMounted (() => {
        window.addEventListener('resize', resizeDiv);
        resizeDiv();
    });

    onBeforeUnmount (() => {
        window.removeEventListener('resize', resizeDiv);
    });
   
    return { resizeDiv };
};