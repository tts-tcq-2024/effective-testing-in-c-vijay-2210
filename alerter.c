#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // Stub always returns 500 for this test case
    return 500;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // Increment the failure count if the return code is not 200
        alertFailureCount += 1;
    }
}

float actualCelicusReceived;
int networkAlertCallCount = 0;

int networkAlertMock(float celcius) {
    actualCelicusReceived = celcius;
    ++networkAlertCallCount;
    return 500;
}

void stateBasedTest() {
    alertInCelcius(400.5);
    assert(alertFailureCount == 1);
}

void behaviorTest() {
    alertInCelcius(303.6);
    assert(alertFailureCount == 2);  // Since stateBasedTest already increments by 1
    float expectedCelToBeReceivedByDependency = (303.6 - 32) * 5 / 9;
    assert(actualCelicusReceived == expectedCelToBeReceivedByDependency);
    assert(networkAlertCallCount == 1);
}

int main() {
    stateBasedTest();
    behaviorTest();
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
