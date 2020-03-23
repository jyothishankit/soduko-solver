#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>tmp(9,0);
vector<vector<ll>>grid(9,tmp);
vector<bool>tmpb(9,1);
vector<vector<bool>>covered(9,tmpb);
vector<set<ll>>cells,boxes,linesRows,linesCols,set3Rows,set3Cols;
vector<ll>iIndexStarts{0,0,0,3,3,3,6,6,6};
vector<ll>jIndexStarts{0,3,6,0,3,6,0,3,6};
set<ll>globalRes;

/*cases
case 2: filled grid - input
case 1: covered or not - boolean grid[][]
case 0: each cell 9 set - 81 sets
case 1: removal taken from cells in box - box set - 9 sets
case 2: removal taken from cells in box - line set - 18 sets
case 3: 3 row/column set and not in other row/column - check
case 4: 2 row/column set and not in other row/column - check
case 5: 1 number in one row/one column and not in other row/column - check
case 6: Replace unfilled one set element with element itself.
case 7: DFS with guess - provided that one can solve without guess.
case 8: XWing.
case 9: Pair wise disjoint.
*/

set<ll> diff(set<ll>a,set<ll>b){
    set<ll>::iterator it;
    set<ll>res;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)==b.end()){
            res.insert(x);
        }
    }
    return res;
}

set<ll> inter(set<ll>&a,set<ll>&b){
    set<ll>::iterator it;
    set<ll>res;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)!=b.end()){
            res.insert(x);
        }
    }
    return res;
}

set<ll> inter3(set<ll>&a,set<ll>&b,set<ll>&c){
    set<ll>::iterator it;
    set<ll>res;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)!=b.end()){
            if(c.find(x)!=c.end()){
                res.insert(x);
            }
        }
    }
    return res;
}


ll findCellPos(ll i,ll j){
    ll pos=i*9+j;
    return pos;
}

ll findBoxPos(ll i,ll j){
    ll pos=(i/3)*3+(j/3);
    return (pos);
}

bool mutuallyExclusive3(ll i,ll j,bool rowWise,set<ll>&a,set<ll>&b,set<ll>&c){
    set<ll>::iterator it;
    set<ll>res;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)!=b.end()){
            if(c.find(x)!=c.end()){
                res.insert(x);
            }
        }
    }
    globalRes=res;
    if(rowWise){
        if((i%3)==0){
            for(ll it=i+1;it<(i+3);++it){
                for(ll jt=j;jt<(j+3);++jt){
                    ll cellpos=findCellPos(it,jt);
                    set<ll>interset=inter(res,cells[cellpos]);
                    globalRes=diff(globalRes,cells[cellpos]);
                }
            }
            if(globalRes.size()>0){
                return 1;
            }
            return 0;
        }
        else if((i%3)==1){
            for(ll it=i-1;it<(i+2);++it){
                if(it==i){
                    continue;
                }
                for(ll jt=j;jt<(j+3);++jt){
                    ll cellpos=findCellPos(it,jt);
                    set<ll>interset=inter(res,cells[cellpos]);
                    globalRes=diff(globalRes,cells[cellpos]);
                }
            }
            if(globalRes.size()>0){
                return 1;
            }
            return 0;
        }
        else{
            for(ll it=i-2;it<(i);++it){
                for(ll jt=j;jt<(j+3);++jt){
                    ll cellpos=findCellPos(it,jt);
                    set<ll>interset=inter(res,cells[cellpos]);
                    globalRes=diff(globalRes,cells[cellpos]);
                }
            }
            if(globalRes.size()>0){
                return 1;
            }
            return 0;
        }
    }
    if((j%3)==0){
        for(ll jt=j+1;jt<(j+3);++jt){
            for(ll it=i;it<(i+3);++it){
                ll cellpos=findCellPos(it,jt);
                set<ll>interset=inter(res,cells[cellpos]);
                globalRes=diff(globalRes,cells[cellpos]);
            }
        }
        if(globalRes.size()>0){
            return 1;
        }
        return 0;
    }
    else if((j%3)==1){
        for(ll jt=j-1;jt<(j+2);++jt){
            if(jt==j){
                continue;
            }
            for(ll it=i;it<(i+3);++it){
                ll cellpos=findCellPos(it,jt);
                set<ll>interset=inter(res,cells[cellpos]);
                globalRes=diff(globalRes,cells[cellpos]);
            }
        }
        if(globalRes.size()>0){
            return 1;
        }
        return 0;
    }
    else{
        for(ll jt=j-2;jt<(j);++jt){
            for(ll it=i;it<(i+3);++it){
                ll cellpos=findCellPos(it,jt);
                set<ll>interset=inter(res,cells[cellpos]);
                globalRes=diff(globalRes,cells[cellpos]);
            }
        }
        if(globalRes.size()>0){
            return 1;
        }
        return 0;
    }
    return 1;
}

// bool mutuallyExclusive2(ll i,ll j,set<ll>&a,set<ll>&b){

// }

void case1(){
    set<ll>tmps;
    boxes.clear();
    boxes.resize(9,tmps);
    for(ll it=0;it<9;++it){
        for(ll i=iIndexStarts[it];i<(iIndexStarts[it]+3);++i){
            for(ll j=jIndexStarts[it];j<(jIndexStarts[it]+3);++j){
                if(covered[i][j]){
                    boxes[it].insert(grid[i][j]);
                }
            }
        }
    }

    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            if(!covered[i][j]){
                ll boxPos=findBoxPos(i,j);
                ll cellPos=findCellPos(i,j);
                set<ll>diffset=diff(cells[cellPos],boxes[boxPos]);
                cells[cellPos]=diffset;
            }
        }
    }
}

void case2(){
    set<ll>tmps;
    linesRows.clear();
    linesRows.resize(9,tmps);
    linesCols.clear();
    linesCols.resize(9,tmps);
    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            if(covered[i][j]){
                linesRows[i].insert(grid[i][j]);
            }
        }
    }
    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            if(!covered[i][j]){
                ll linesPos=i;
                ll cellPos=findCellPos(i,j);
                set<ll>diffset=diff(cells[cellPos],linesRows[linesPos]);
                cells[cellPos]=diffset;
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll i=0;i<9;++i){
            if(covered[i][j]){
                linesCols[j].insert(grid[i][j]);
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll i=0;i<9;++i){
            if(!covered[i][j]){
                ll linesPos=j;
                ll cellPos=findCellPos(i,j);
                set<ll>diffset=diff(cells[cellPos],linesCols[linesPos]);
                cells[cellPos]=diffset;
            }
        }
    }
}

vector<ll> findVec(set<ll>st){
    set<ll>::iterator it;
    vector<ll>res;
    for(it=st.begin();it!=st.end();it++){
        ll x=(*it);
        res.push_back(x);
    }
    return res;
}

void case3(){
    for(ll i=0;i<9;++i){
        for(ll it=0;it<3;++it){
            ll cellpos=findCellPos(i, it*3);
            globalRes.clear(); 
    if(mutuallyExclusive3(i,it*3,1,cells[cellpos],cells[cellpos+1],cells[cellpos+2])){
                set<ll> inter3set = globalRes;
                if(inter3set.size()==3){
                    cells[cellpos]=inter3set;
                    cells[cellpos+1]=inter3set;
                    cells[cellpos+2]=inter3set;
                }
                vector<ll> setElements = findVec(inter3set);
                for(ll j=0;j<9;++j){
                    if(covered[i][j]){
                        continue;
                    }
                    if((j>=(it*3))&&(j<((it*3)+3))){
                        continue;
                    }
                    ll cellpos=findCellPos(i,j);
                    for(ll itv=0;itv<setElements.size();++itv){
                        ll x=setElements[itv];
                        cells[cellpos].erase(x);
                    }
                }
            }
            globalRes.clear();
        }
    }
    for(ll j=0;j<9;++j){
        for(ll it=0;it<3;++it){
            ll cellpos=findCellPos(it*3,j); 
            globalRes.clear();
    if(mutuallyExclusive3(it*3,j,0,cells[cellpos],cells[cellpos+9],cells[cellpos+18])){
                set<ll> inter3set = globalRes;
                if(inter3set.size()==3){
                    cells[cellpos]=inter3set;
                    cells[cellpos+9]=inter3set;
                    cells[cellpos+18]=inter3set;
                }          
                vector<ll> setElements = findVec(inter3set);
                for(ll i=0;i<9;++i){
                    if(covered[i][j]){
                        continue;
                    }
                    if((i>=(it*3))&&(i<((it*3)+3))){
                        continue;
                    }
                    ll cellpos=findCellPos(i,j);
                    for(ll itv=0;itv<setElements.size();++itv){
                       ll x=setElements[itv];
                       cells[cellpos].erase(x);
                    }
                }
            }
            globalRes.clear();
        }
    }
}

bool checkWhetherMutual1(ll ix,ll j1,ll j2,set<ll>&res){
    //vector<ll>iIndexStarts{0,0,0,3,3,3,6,6,6};
    //vector<ll>jIndexStarts{0,3,6,0,3,6,0,3,6};
    ll boxNum = findBoxPos(ix,j1);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((i==ix)&&((j==j1)||(j==j2))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }

    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}

bool checkWhetherMutual2(ll ix,ll j2,ll j3,set<ll>&res){
    ll boxNum = findBoxPos(ix,j2);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((i==ix)&&((j==j2)||(j==j3))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }
    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}

bool checkWhetherMutual3(ll jx,ll i1,ll i2,set<ll>&res){
    ll boxNum = findBoxPos(i1,jx);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((j==jx)&&((i==i1)||(i==i2))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }
    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}

bool checkWhetherMutual4(ll jx,ll i2,ll i3,set<ll>&res){
    ll boxNum = findBoxPos(i2,jx);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((j==jx)&&((i==i2)||(i==i3))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }
    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}

bool checkWhetherMutual5(ll ix,ll j1,ll j3,set<ll>&res){
    ll boxNum = findBoxPos(ix,j1);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((i==ix)&&((j==j1)||(j==j3))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }
    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}


bool checkWhetherMutual6(ll jx,ll i1,ll i3,set<ll>&res){
    ll boxNum = findBoxPos(i1,jx);
    set<ll>::iterator it;
    for(it=res.begin();it!=res.end();++it){
        ll x=(*it);
        for(ll i=iIndexStarts[boxNum];i<(iIndexStarts[boxNum]+3);++i){
            for(ll j=jIndexStarts[boxNum];j<(jIndexStarts[boxNum]+3);++j){
                if((j==jx)&&((i==i1)||(i==i3))){
                    continue;
                }
                ll cellpos=findCellPos(i,j);
                globalRes = diff(globalRes,cells[cellpos]);
            }
        }
    }
    if(globalRes.size()>0){
        return 1;
    }
    return 0;
}

void case4(){
    
    // case 2 element mutual all cases, row column, 2 opposite, line erase.

    for(ll i=0;i<9;++i){
        for(ll jt=0;jt<9;jt+=3){
            ll j1=jt,j2=jt+1,j3=jt+2;
            //set<ll> inter(set<ll>&a,set<ll>&b){
            ll cellpos1=findCellPos(i,j1);
            ll cellpos2=findCellPos(i,j2);
            ll cellpos3=findCellPos(i,j3);
            set<ll>res1=inter(cells[cellpos1],cells[cellpos2]);
            globalRes.clear();
            if(res1.size()>0){
                globalRes = res1;
                if(checkWhetherMutual1(i,j1,j2,res1)){
                    if(globalRes.size()==2){
                        cells[cellpos1]=globalRes;
                        cells[cellpos2]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll j=0;j<9;++j){
                        if((j>=j1)&&(j<=j3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
            set<ll>res2=inter(cells[cellpos2],cells[cellpos3]);
            globalRes.clear();
            if(res2.size()>0){
                globalRes = res2;
                if(checkWhetherMutual2(i,j2,j3,res2)){
                    if(globalRes.size()==2){
                        cells[cellpos3]=globalRes;
                        cells[cellpos2]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll j=0;j<9;++j){
                        if((j>=j1)&&(j<=j3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll it=0;it<9;it+=3){
            ll i1=it,i2=it+1,i3=it+2;
            //set<ll> inter(set<ll>&a,set<ll>&b){
            ll cellpos1=findCellPos(i1,j);
            ll cellpos2=findCellPos(i2,j);
            ll cellpos3=findCellPos(i3,j);
            set<ll>res1=inter(cells[cellpos1],cells[cellpos2]);
            globalRes.clear();
            if(res1.size()>0){
                globalRes = res1;
                if(checkWhetherMutual3(j,i1,i2,res1)){
                    if(globalRes.size()==2){
                        cells[cellpos1]=globalRes;
                        cells[cellpos2]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll i=0;i<9;++i){
                        if((i>=i1)&&(i<=i3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
            set<ll>res2=inter(cells[cellpos2],cells[cellpos3]);
            globalRes.clear();
            if(res2.size()>0){
                globalRes = res2;
                if(checkWhetherMutual4(j,i2,i3,res2)){
                    if(globalRes.size()==2){
                        cells[cellpos3]=globalRes;
                        cells[cellpos2]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll i=0;i<9;++i){
                        if((i>=i1)&&(i<=i3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
        }
    }

    for(ll i=0;i<9;++i){
        for(ll jt=0;jt<9;jt+=3){
            ll j1=jt,j2=jt+1,j3=jt+2;
            //set<ll> inter(set<ll>&a,set<ll>&b){
            ll cellpos1=findCellPos(i,j1);
            ll cellpos3=findCellPos(i,j3);
            set<ll>res1=inter(cells[cellpos1],cells[cellpos3]);
            globalRes.clear();
            if(res1.size()>0){
                globalRes = res1;
                if(checkWhetherMutual5(i,j1,j3,res1)){
                    if(globalRes.size()==2){
                        cells[cellpos1]=globalRes;
                        cells[cellpos3]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll j=0;j<9;++j){
                        if((j>=j1)&&(j<=j3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll it=0;it<9;it+=3){
            ll i1=it,i2=it+1,i3=it+2;
            //set<ll> inter(set<ll>&a,set<ll>&b){
            ll cellpos1=findCellPos(i1,j);
            ll cellpos3=findCellPos(i3,j);
            set<ll>res1=inter(cells[cellpos1],cells[cellpos3]);
            globalRes.clear();
            if(res1.size()>0){
                globalRes = res1;
                if(checkWhetherMutual6(j,i1,i3,res1)){
                    if(globalRes.size()==2){
                        cells[cellpos1]=globalRes;
                        cells[cellpos3]=globalRes;
                    }
                    vector<ll>setElements = findVec(globalRes);
                    for(ll i=0;i<9;++i){
                        if((i>=i1)&&(i<=i3)){
                            continue;
                        }
                        ll sz=setElements.size();
                        for(ll itv=0;itv<sz;++itv){
                            ll x=setElements[itv];
                            ll cellposx=findCellPos(i,j);
                            cells[cellposx].erase(x);
                        }
                    }
                }
            }
        }
    }

}

void case5(){

    //case 1 : boxes 1 element in set and replace

    vector<ll>iIndexStarts{0,0,0,3,3,3,6,6,6};
    vector<ll>jIndexStarts{0,3,6,0,3,6,0,3,6};
    for(ll num=1;num<=9;++num){
        for(ll it=0;it<9;++it){
            ll count=0;
            ll posi=-1,posj=-1;
            ll cellposij=-1;
            bool flag=0;
            for(ll i=iIndexStarts[it];i<(iIndexStarts[it]+3);++i){
                for(ll j=jIndexStarts[it];j<(jIndexStarts[it]+3);++j){
                    ll cellpos=findCellPos(i,j);
                    if(covered[i][j] && (grid[i][j]==num)){
                        ++count;
                        flag=1;
                    }
                    if((!covered[i][j]) && cells[cellpos].find(num)!=cells[cellpos].end()){
                        ++count;
                        posi=i;
                        posj=j;
                        cellposij=cellpos;
                    }
                }
            }
            if((!flag)&&(count==1)){
                set<ll>tmp;
                tmp.insert(num);
                cells[cellposij]=tmp;
                grid[posi][posj]=num;
                covered[posi][posj]=1;
            }
        }
    }
    
    //case 2 : lines 1 element present and replace

    for(ll i=0;i<9;++i){
        for(ll num=1;num<=9;++num){
            ll count=0;
            bool flag=0;
            ll posi=-1,posj=-1,cellposij=-1;
            for(ll j=0;j<9;++j){
                ll cellpos = findCellPos(i,j);
                if(covered[i][j] && (grid[i][j]==num)){
                    ++count;
                    flag=1;
                }
                if((!covered[i][j]) && (cells[cellpos].find(num)!=cells[cellpos].end())){
                    ++count;
                    posi=i;
                    posj=j;
                    cellposij=cellpos;
                }       
            }
            if((!flag)&&(count==1)){
                set<ll>tmp;
                tmp.insert(num);
                cells[cellposij]=tmp;
                grid[posi][posj]=num;
                covered[posi][posj]=1;
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll num=1;num<=9;++num){
            ll count=0;
            bool flag=0;
            ll posi=-1,posj=-1,cellposij=-1;
            for(ll i=0;i<9;++i){
                ll cellpos = findCellPos(i,j);
                if(covered[i][j] && (grid[i][j]==num)){
                    ++count;
                    flag=1;
                }
                if((!covered[i][j]) && (cells[cellpos].find(num)!=cells[cellpos].end())){
                    ++count;
                    posi=i;
                    posj=j;
                    cellposij=cellpos;
                }       
            }
            if((!flag)&&(count==1)){
                set<ll>tmp;
                tmp.insert(num);
                cells[cellposij]=tmp;
                grid[posi][posj]=num;
                covered[posi][posj]=1;
            }
        }
    }
    
}


void case6(){
    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            //cout<<grid[i][j];
            if(!covered[i][j]){
                ll cellpos=findCellPos(i,j);
                if(cells[cellpos].size()==1){
                    vector<ll>setElements=findVec(cells[cellpos]);
                    grid[i][j]=setElements[0];
                    covered[i][j]=1;
                }
            }
        }
        //cout<<"\n";
    }
    //  cout<<"##################################\n";
    //  cout<<"##################################\n";

    //  set<ll>::iterator it;
    //  for(it=cells[8].begin();it!=cells[8].end();++it){
    //      ll x=(*it);
    //      cout<<x<<" ";
    //  }
    //  cout<<"\n@@@@@@@@@@@@@@@@@@@@@@\n";
}


bool filled(){
    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            if(!covered[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

bool checkIfTwoDistinct1(ll i,ll j1,ll j2,set<ll>&a,set<ll>&b){
    set<ll>res;
    set<ll>::iterator it;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)!=b.end()){
            res.insert(x);
        }
    }
    globalRes=res;
    for(ll j=0;j<9;++j){
        if((j==j1)||(j==j2)){
            continue;
        }
        ll cellpos=findCellPos(i,j);
        globalRes=diff(globalRes,cells[cellpos]);
    }
    if(globalRes.size()==2){
        return 1;
    }
    return 0;
}

bool checkIfTwoDistinct2(ll j,ll i1,ll i2,set<ll>&a,set<ll>&b){
    set<ll>res;
    set<ll>::iterator it;
    for(it=a.begin();it!=a.end();it++){
        ll x=(*it);
        if(b.find(x)!=b.end()){
            res.insert(x);
        }
    }
    globalRes=res;
    for(ll i=0;i<9;++i){
        if((i==i1)||(i==i2)){
            continue;
        }
        ll cellpos=findCellPos(i,j);
        globalRes=diff(globalRes,cells[cellpos]);
    }
    if(globalRes.size()==2){
        return 1;
    }
    return 0;
}

void case7(){
    for(ll i=0;i<9;++i){
        for(ll j1=0;j1<8;++j1){
            for(ll j2=j1+1;j2<9;++j2){
                if(covered[i][j1] || covered[i][j2]){
                    continue;
                }
                globalRes.clear();
                ll cellpos1=findCellPos(i,j1);
                ll cellpos2=findCellPos(i,j2);
                if(checkIfTwoDistinct1(i,j1,j2,cells[cellpos1],cells[cellpos2])){
                    cells[cellpos1]=globalRes;
                    cells[cellpos2]=globalRes;
                    vector<ll> setElements = findVec(globalRes);
                    for(ll j=0;j<9;++j){
                        if((j==j1)||(j==j2)||covered[i][j]){
                            continue;
                        }
                        ll cellpos=findCellPos(i,j);
                        cells[cellpos].erase(setElements[0]);
                        cells[cellpos].erase(setElements[1]);
                    }
                }
            }
        }
    }

    for(ll j=0;j<9;++j){
        for(ll i1=0;i1<8;++i1){
            for(ll i2=i1+1;i2<9;++i2){
                if(covered[i1][j] || covered[i2][j]){
                    continue;
                }
                globalRes.clear();
                ll cellpos1=findCellPos(i1,j);
                ll cellpos2=findCellPos(i2,j);
                if(checkIfTwoDistinct2(j,i1,i2,cells[cellpos1],cells[cellpos2])){
                    cells[cellpos1]=globalRes;
                    cells[cellpos2]=globalRes;
                    vector<ll> setElements = findVec(globalRes);
                    for(ll i=0;i<9;++i){
                        if((i==i1)||(i==i2)||covered[i][j]){
                            continue;
                        }
                        ll cellpos=findCellPos(i,j);
                        cells[cellpos].erase(setElements[0]);
                        cells[cellpos].erase(setElements[1]);
                    }
                }
            }
        }
    }
}

/// X-Wing factor
void case8(){
    for(ll num=1;num<=9;++num){
        for(ll j1=0;j1<8;++j1){
            for(ll j2=j1+3;j2<9;++j2){
                ll ai=-1,bi=-1,count=0;
                for(ll i=0;i<9;++i){
                    ll cellpos1=findCellPos(i,j1);
                    ll cellpos2=findCellPos(i,j2);
                    bool cond1=(cells[cellpos1].find(num)!=cells[cellpos1].end());
                    bool cond2=(cells[cellpos2].find(num)!=cells[cellpos2].end());
                    if(cond1 && cond2){ 
                        ++count;
                        if(ai==-1){
                            ai=i;
                        }else{
                            bi=i;
                        }
                    }    
                }
                if(count==2){
                    for(ll j=0;j<9;++j){
                        if((j==j1)||(j==j2)){
                            continue;
                        }
                        if(!covered[ai][j]){
                            ll cellpos1=findCellPos(ai,j);
                            cells[cellpos1].erase(num);
                        }
                        if(!covered[bi][j]){
                            ll cellpos2=findCellPos(bi,j);
                            cells[cellpos2].erase(num);
                        }
                    }
                    for(ll i=0;i<9;++i){
                        if((i==ai)||(i==bi)){
                            continue;
                        }
                        if(!covered[i][j1]){
                            ll cellpos1=findCellPos(i,j1);
                            cells[cellpos1].erase(num);
                        }
                        if(!covered[i][j2]){
                            ll cellpos2=findCellPos(i,j2);
                            cells[cellpos2].erase(num);
                        }
                    }
                }
            }
        }
    }
}

void solve(){
    ll count=0;
    while(!filled()){
        //if(count!=7){++count;}
        case1();
        case5();
        case2();
        case5();
        case3();
        case5();
        case4();
        case5();
        case7();
        // if(count==7){
        //     case8();
        // }
        case6();
    }
}

int main() {
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    string s;
    set<ll>tmps;
    cells.resize(81,tmps);
    for(ll i=0;i<9;++i){
        cin>>s;
        for(ll j=0;j<9;++j){
            grid[i][j]=s[j]-'0';
            ll pos=findCellPos(i,j);
            if(!grid[i][j]){
                covered[i][j]=0;
                for(ll i=1;i<=9;++i){
                    cells[pos].insert(i);
                }
            }else{
                cells[pos].insert(grid[i][j]);
            }
        }
    }
    // cout<<"##################################\n";
    // cout<<"##################################\n";

    //  set<ll>::iterator it;
    //  for(it=cells[8].begin();it!=cells[8].end();++it){
    //      ll x=(*it);
    //      cout<<x<<" ";
    //  }
    //  cout<<"\n@@@@@@@@@@@@@@@@@@@@@@\n";
    solve();
    for(ll i=0;i<9;++i){
        for(ll j=0;j<9;++j){
            cout<<grid[i][j];
        }
        cout<<"\n";
    }    
    return 0;
}

