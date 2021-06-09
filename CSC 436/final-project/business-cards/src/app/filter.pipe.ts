import { Pipe, PipeTransform } from '@angular/core';

import { BusinessCard } from './business-card.model';

@Pipe({
  name: 'filter'
})
export class FilterPipe implements PipeTransform {
  transform(cards: BusinessCard[], searchText: string): BusinessCard[] {
    if(!cards) return [];
    if(!searchText) return cards;
    
    searchText = searchText.toLowerCase();
    
    return cards.filter(card => {
      return (
        (card.firstName + " " + card.lastName).toLowerCase().includes(searchText) ||
        card.company.toLowerCase().includes(searchText) ||
        card.emailAddress.toLowerCase().includes(searchText) ||
        card.phoneNumber.toLowerCase().includes(searchText) || 
        card.additionalInfo.toLowerCase().includes(searchText)
      );
    });
   }
}