import * as Juce from 'juce-framework-frontend';
import { JuceHelpers } from '../JuceHelpers';

import { ref, onBeforeUnmount } from 'vue'

export default function useLicensing () {
    
    
    class LicensingInfo {
        constructor () {
            this.serviceId = "";
            
            this.productId = "";
            this.offlineUrl = "";
            this.companyName = "";
            this.productName = "";
            this.productVersion = "";
            
            this.userEmail = "";
            this.licenseId = "";
            
            this.isUnlocked = false;
            this.isTrial = false;
            this.isOfflineActivated = false;
            
            this.expiry = 0;
        };

        getUserFriendlyExpiry () {
            if (this.expiry === 0) {
                return "No expiry";
            } else {
                const date = new Date (this.expiry);
                return date.toLocaleDateString ();
            }
        }

        getUserIdentification () {
            return this.isTrial ? "Trial" : this.userEmail;
        }

        getLicenseId () {
            return this.licenseId;
        }

        isRunningLicensing () {
            return this.serviceId !== "none";
        }

        mustBeVisible () {
            // return false
            return this.isRunningLicensing () && ! this.isUnlocked;
        }
    };

    const licensingInfo = ref(null);

    updateLicensingInfoFromBackend ();

    const userRequestedVisibility = ref(false); 

    function getVersion () {
        return licensingInfo?.value?.productVersion;
    }

    function isRunningLicensing () {
        return licensingInfo?.value?.isRunningLicensing ();
    }

    function getActivationType () {
        return  ! licensingInfo?.value?.isUnlocked ? "Not Activated" :
                licensingInfo?.value?.isTrial ? "Trial" : 
                licensingInfo?.value?.isOfflineActivated ? "Offline" : "Online";
    }

    function getUserIdentification () {
        return licensingInfo?.value?.getUserIdentification ();
    }

    function getLicenseId () {
        return licensingInfo?.value?.getLicenseId ();
    }
    
    function mustBeVisible () {
        return licensingInfo?.value?.mustBeVisible ();
    }

    function shouldBeVisible () {
        return userRequestedVisibility.value || mustBeVisible ();
    }

    function isFullyActivated () {
        return licensingInfo?.value?.isUnlocked && ! licensingInfo?.value?.isTrial;
    }

    function isTrialActivated () {
        return licensingInfo?.value?.isUnlocked && licensingInfo?.value?.isTrial;
    }

    function requestVisibility (visible) {
        if (! mustBeVisible () && isRunningLicensing ())
            userRequestedVisibility.value = visible;
        else userRequestedVisibility.value = false;
    }

    function requestToggleVisibility () {
        if (! mustBeVisible () && isRunningLicensing ())
            userRequestedVisibility.value = ! userRequestedVisibility.value;
        else userRequestedVisibility.value = false;
    }

    function updateLicensingInfoFromBackend () {
        JuceHelpers.callJuceNativeReturn ("getLicensingInfo").then ((result) => {
            if (result === null) {
                console.error ("Error getting licensing info");
                return;
            }
            if (result.warning !== null) {
                console.warn (result.warning);
            }
            
            licensingInfo.value = new LicensingInfo ();
            if (result.serviceId !== null) {
                licensingInfo.value.serviceId = result.serviceId;
                licensingInfo.value.productId = result.productId;
                licensingInfo.value.offlineUrl = result.offlineUrl;
                licensingInfo.value.companyName = result.companyName;
                licensingInfo.value.productName = result.productName;
                licensingInfo.value.productVersion = result.productVersion;
                licensingInfo.value.userEmail = result.userEmail;
                licensingInfo.value.licenseId = result.licenseId;
                licensingInfo.value.isUnlocked = result.isUnlocked;
                licensingInfo.value.isTrial = result.isTrial;
                licensingInfo.value.isOfflineActivated = result.isOfflineActivated;
                licensingInfo.value.expiry = result.expiry;
            }

            console.log ("Updated License info: ", licensingInfo.value);
        });
    }

    let autoActivationListenerId = null;
    let autoActivationFinishedCallback = null;
    function requestAutoActivation (finishedCallback = null) {
        console.log ("Requesting auto activation");
        autoActivationFinishedCallback = finishedCallback;
        JuceHelpers.callJuceNativeReturn ("requestAutoActivation").then ((result) => {
            console.log ("Auto activation result: ", result);
            if (result.result) {
                //open new browser window on result.browserUrl
                
                JuceHelpers.callJuceNativeReturn ("openInExternalBrowserWindow", result.browserUrl);
                
                JuceHelpers.callJuceNativeReturn ("startPollingActivationStatus").then ((result) => {
                    console.log ("Polling activation status result: ", result);
                    if (result.result) {
                        autoActivationListenerId = window.__JUCE__.backend.addEventListener (
                            result.listenerId, 
                            (eventArr) => {
                                const event = eventArr[0];
                                console.log ("Poll status: ", event);
                         
                                if (event.finished) { 
                                    
                                    if (event.success)
                                        updateLicensingInfoFromBackend ();
                                    
                                    if (autoActivationListenerId !== null)
                                        window.__JUCE__.backend.removeEventListener (autoActivationListenerId);

                                    if (autoActivationFinishedCallback !== null) {
                                        autoActivationFinishedCallback (event.success);
                                        autoActivationFinishedCallback = null;
                                    }
                                }     
                       
                            }
                        );
                    } else {
                        console.error ("Error starting polling activation status");
                    }
                });

  
            } else {
                console.error ("Error requesting auto activation");
            }
        });
    }

    function interruptAutoActivation () {
        console.log ("interrupting auto activation");
        JuceHelpers.callJuceNativeReturn ("stopPollingActivationStatus").then ((result) => {
            console.log ("interruptAutoActivation result: ", result);
        });
    }

    let successCallback = null;
    function generateMachineFile (successCallback_) {
        console.log ("Generating machine file");
        successCallback = successCallback_;
        JuceHelpers.callJuceNativeReturn ("generateMachineFile").then ((result) => {
            console.log ("generateMachineFile result: ", result);
            if (result.result) {
                if (successCallback !== null) {
                    successCallback (result.machineFile);
                    successCallback = null;
                }
            }

        });
    }

    function deactivateLicense () {
        console.log ("Deactivating license");
        JuceHelpers.callJuceNativeReturn ("deactivateLicense").then ((result) => {
            console.log ("deactivateLicense result: ", result);
            if (result.result) {
                updateLicensingInfoFromBackend ();
            }
        });
    }


    //gotta refactor this into the general juce helpers
    function openInExternalBrowserWindow (url) {
        JuceHelpers.callJuceNativeReturn ("openInExternalBrowserWindow", url);
    }

    onBeforeUnmount (() => {
        if (autoActivationListenerId !== null)
            window.__JUCE__.backend.removeEventListener (autoActivationListenerId);

        if (successCallback !== null)
            successCallback = null;
    });

    return {
        licensingInfo,
        shouldBeVisible,
        mustBeVisible,
        requestVisibility,
        requestToggleVisibility,
        requestAutoActivation,
        interruptAutoActivation,
        generateMachineFile,
        openInExternalBrowserWindow,
        isFullyActivated,
        isTrialActivated,
        deactivateLicense,
        getVersion,
        getActivationType,
        getUserIdentification,
        getLicenseId
    };
}; 