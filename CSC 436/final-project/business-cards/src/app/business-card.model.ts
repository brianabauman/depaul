export interface IBusinessCard {
    firstName: string;
    lastName: string;
    phoneNumber: string;
    emailAddress: string;
    company: string;
    additionalInfo: string;
}

export class BusinessCard implements IBusinessCard {
    firstName: string;
    lastName: string;
    phoneNumber: string;
    emailAddress: string;
    company: string;
    additionalInfo: string;
    //imageBase64: string;

    constructor() {
        this.firstName = "";
        this.lastName = "";
        this.phoneNumber = "";
        this.emailAddress = "";
        this.company = "";
        this.additionalInfo = "";
    }
}